#pragma once

#include "ftp_command.h"

class UserCommand : FTPCommand {
 public:
  std::string Keyword() const override { return "USER"; }
  
  void Run() const override {
    
  }

};
