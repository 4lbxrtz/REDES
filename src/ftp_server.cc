#pragma once

#include <cerrno>
#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <thread>
#include <list>

#include "ftp_server.h"
#include "client_connection.h"
#include "utility.h"

void FTPServer::DefineSocketTCP() {
  tcp_socket_ = socket(AF_INET, SOCK_STREAM, 0);
  if (tcp_socket_ < 0) {
    throw std::system_error(errno, std::system_category());
  }

  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(port_);

  if (bind(tcp_socket_, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    throw std::system_error(errno, std::system_category());
  }

  if (listen(tcp_socket_, 5) < 0) {
    throw std::system_error(errno, std::system_category());
  }
}

void RunClientConnection(const FTPServer& server, ClientConnection* connection) {
  connection->WaitForRequests(server);
}

void FTPServer::Stop() {
  close(tcp_socket_);
  shutdown(tcp_socket_, SHUT_RDWR);
}

void FTPServer::Run() {
  try {
    std::cout << "Starting the server..." << std::endl;
    struct sockaddr_in input_socket;
    int server_socket;
    socklen_t socket_length = sizeof(input_socket);
    DefineSocketTCP();  // This function must be implemented by you.
    std::vector<std::thread> threads;
    while (true) {
      std::cout << "Waiting for new connections..." << std::endl;
      std::cout << "Waiting for TCP socket to become available..." << std::endl;
      server_socket = accept(tcp_socket_, (struct sockaddr *)&input_socket, &socket_length);
      if(server_socket < 0) {
        throw std::system_error(errno, std::system_category());      
      }
      std::cout << "New connection received on the command socket, socket file descriptor is " << server_socket << ", IP address: "
      << inet_ntoa(input_socket.sin_addr) << ", port : " << ntohs(input_socket.sin_port) << std::endl;
      ClientConnection *connection = new ClientConnection(server_socket);
      threads.emplace_back(RunClientConnection, *this, connection);  // same as old pthread_create(&thread, NULL, run_client_connection, (void*)connection);
    }
  } catch (...) {
    std::throw_with_nested(std::runtime_error("An error occurred while running the FTPServer"));
  } 
}
