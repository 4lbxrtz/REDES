#pragma once

#include <pthread.h>

#include <cstdio>
#include <cstdint>

const int kMaxBuffer = 1000;

class FTPServer;

class ClientConnection {
 public:
  ClientConnection(int data_socket);
  ~ClientConnection();

  inline int GetDataSocket() const { return data_socket_; }
  inline int GetControlSocket() const { return control_socket_; }
  inline char* GetArguments() { return arguments_; }
  inline FILE* GetFileDescriptor() { return file_descriptor_; }
  inline int IsOk() const { return is_ok_; }
  
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
