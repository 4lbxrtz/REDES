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
  int sock = socket;
  char buffer[kMaxBuffer];
  control_socket_ = socket;
  file_descriptor_ = fdopen(socket, "a+");
  if (file_descriptor_ == NULL) {
    std::cout << "Connection closed" << std::endl;
    fclose(file_descriptor_); // maybe comentar esta linea
    close(control_socket_);
    is_ok_ = false;
    return;
  }
  is_ok_ = true;
  data_socket_ = -1;
  is_stop_ = false;
}

ClientConnection::~ClientConnection() {
  if (is_ok_) {
 	  fclose(file_descriptor_);
	  close(control_socket_); 
  }
}

int ConnectTCP(uint32_t address,  uint16_t  port) {
  try {

  } catch (...) {
    std::throw_with_nested(std::runtime_error("An error occurred while defining the socket descriptor."));
  }
  return -1; // You must return the socket descriptor.
}

void ClientConnection::Stop() {
  close(data_socket_);
  close(control_socket_);
  is_stop_ = true;
}
 
#define COMMAND(cmd) strcmp(command, cmd) == 0

void ClientConnection::WaitForRequests(const FTPServer& server) {
  if (!is_ok_) {
    return;
  }
  while(true) {
    char command[kMaxBuffer];
    fscanf(file_descriptor_, "%s", command);
    std::string command_string(command);
    auto& archive = server.GetCommandsArchive();
    archive.Execute(command_string);
  }
}
