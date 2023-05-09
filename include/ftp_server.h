#pragma once

#include <list>

#include "ftp_commands_archive.h"

class ClientConnection;

class FTPServer {
 public:
  FTPServer(const FTPCommandsArchive& command_record, const int port = 21) :
   command_record_(command_record), port_(port) { }
  FTPServer(const int port) :
   FTPServer(FTPCommandsArchive()) { }

  const inline FTPCommandsArchive& GetCommandsArchive() const { return command_record_; }
  
  void Run();
  void Stop();

 private:
  FTPCommandsArchive command_record_;
  int port_;
  int tcp_socket_;
  std::list<ClientConnection> connection_list_;
};
