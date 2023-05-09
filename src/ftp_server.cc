#pragma once

#include <cerrno>
#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <netdb.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>

#include <pthread.h>

#include <thread>
#include <list>

#include "ftp_server.h"
#include "client_connection.h"
#include "utils.h"

int DefineSocketTCP(int port) {


  return -1;
}

void* RunClientConnection(const FTPServer& server, ClientConnection* connection) {
  connection->WaitForRequests(server);
  return NULL;
}

FTPServer::FTPServer(int port) {
  this->port_ = port;
}

void FTPServer::Stop() {
  close(tcp_socket_);
  shutdown(tcp_socket_, SHUT_RDWR);
}

void FTPServer::Run() {
  try {
    struct sockaddr_in input_socket;
    int server_socket;
    socklen_t length = sizeof(input_socket);
    tcp_socket_ = DefineSocketTCP(port_);  // This function must be implemented by you.
    while (true) {
      server_socket = accept(tcp_socket_, (struct sockaddr *)&input_socket, &length);
      if(server_socket < 0) {
        throw std::system_error(errno, std::system_category());      
      }
      ClientConnection *connection = new ClientConnection(server_socket);
      std::thread thread(RunClientConnection, *this, connection);  // same as old pthread_create(&thread, NULL, run_client_connection, (void*)connection);
    }
  } catch (...) {
    std::throw_with_nested(std::runtime_error("An error occurred while running the FTPServer"));
  } 
}
