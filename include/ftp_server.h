#pragma once

#include <list>

#include "client_connection.h"

class FTPServer {
 public:
  FTPServer(const int port = 21) :
   port_(port), tcp_socket_(-1), connection_list_() { }

  void DefineSocketTCP();

  void Run();
  void Stop();

 private:
  int port_;
  int tcp_socket_;
  std::list<ClientConnection> connection_list_;
};
