#pragma once

#include <pthread.h>

#include <cstdio>
#include <cstdint>

const int kMaxBuffer = 1000;

class FTPServer;

class ClientConnection {
 public:
  ClientConnection(int data_socket) : data_socket_(data_socket) { }
  ~ClientConnection();

  void WaitForRequests(const FTPServer& server);
  void Stop();

 private:
  int data_socket_;
  int control_socket_;
  char arguments_[kMaxBuffer];
  bool is_ok_;
  bool is_stop_;
  FILE *file_descriptor_;
};
