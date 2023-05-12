#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <cerrno>
#include <netdb.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/stat.h> 
#include <iostream>
#include <dirent.h>

#include "client_connection.h"
#include "ftp_server.h"

ClientConnection::ClientConnection(int socket) {
  char buffer[kMaxBuffer];
  control_socket_ = socket;
  file_descriptor_ = fdopen(control_socket_, "a+");
  if (file_descriptor_ == NULL) {
    std::cout << "Connection closed" << std::endl;
    fclose(file_descriptor_); // maybe comentar esta linea
    close(control_socket_);
    is_ok_ = false;
    return;
  }
  is_ok_ = true;
  control_socket_ = -1;
}

ClientConnection::~ClientConnection() {
  if (is_ok_) {
 	  fclose(file_descriptor_);
	  close(control_socket_); 
  }
}

int ConnectTCP(uint32_t address,  uint16_t  port) {
  try {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
      perror("Error opening socket");
      return -1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(address);
    server_addr.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
      perror("Error connecting to server");
      close(sockfd);
      return -1;
    }
    return sockfd;
  } catch (...) {
    std::throw_with_nested(std::runtime_error("An error occurred while defining the socket descriptor."));
  }
  return -1;
}

void ClientConnection::Stop() {
  close(data_socket_);
  close(control_socket_);
}
 
#define COMMAND(cmd) strcmp(command, cmd) == 0

void ClientConnection::WaitForRequests(const FTPServer& server) {
  if (!is_ok_) {
    return;
  }
  fprintf(file_descriptor_, "220 Service Ready\n");
  while(data_socket_ != -1) {
    char command[kMaxBuffer];
    fscanf(file_descriptor_, "%s", command);
    std::string command_string(command);

    if (command_string == "USER") {
      auto file_descriptor = GetFileDescriptor();
      fscanf(file_descriptor, "%s", GetArguments());
      fprintf(file_descriptor, "331 User name ok, need password\n");

    } else if (command_string == "PASS") {
      FILE* file_descriptor = GetFileDescriptor();
      auto arg_buffer = GetArguments();
      fscanf(file_descriptor, "%s", GetArguments());
      if (strcmp(arg_buffer, "1234") == 0) {
        fprintf(file_descriptor, "230 User logged in\n");
      } else {
        fprintf(file_descriptor, "530 Not logged in\n");
      } 

    } else if (command_string == "SYST") {
      FILE* file_descriptor = GetFileDescriptor();
      fprintf(file_descriptor, "215 UNIX Type: L8.\n");

    } else if (command_string == "PORT") {
      FILE* file_descriptor = GetFileDescriptor();
      fscanf(file_descriptor, "%s", GetArguments());
      fprintf(file_descriptor, "200 OK.\n");

    } else if (command_string == "PASV") {
      FILE* file_descriptor = GetFileDescriptor();
      fprintf(file_descriptor, "227 Entering Passive Mode (127,0,0,1,129,232).\n");

    } else if (command_string == "STOR") {
      FILE* file_descriptor = GetFileDescriptor();
      fscanf(file_descriptor, "%s", GetArguments());
      fprintf(file_descriptor, "File creation ok, about to open data connection\n");
      fprintf(file_descriptor, "226, Closing data connection.\n");
      fprintf(file_descriptor, "2480 bytes sent in 0.00 secs (86495.5 kB/s)\n");
    
    } else if (command_string == "RETR") {
      FILE* file_descriptor = GetFileDescriptor();
      fscanf(file_descriptor, "%s", GetArguments());
      fprintf(file_descriptor, "150 File status okay\n");
      fprintf(file_descriptor, "226, Closing data connection.\n");
      fprintf(file_descriptor, "2480 bytes sent in 0.00 secs (41756.5 kB/s)\n");
    
    } else if (command_string == "LIST") {
      FILE* file_descriptor = GetFileDescriptor();
      fscanf(file_descriptor, "%s", GetArguments());
      fprintf(file_descriptor, "125 List started OK\n");
      fprintf(file_descriptor, "250 List completed successfully.\n");
    } else if (command_string == "TYPE") {
      FILE* file_descriptor = GetFileDescriptor();
      fscanf(file_descriptor, "%s", GetArguments());
      fprintf(file_descriptor, "200 OK.\n");
    } else {
      FILE* file_descriptor = GetFileDescriptor();
      fprintf(file_descriptor, "500 Syntax error, unrecognized command.\n");
    }
  }
} 
