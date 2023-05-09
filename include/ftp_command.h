#pragma once

#include <string>

class FTPCommand {
 public:
  virtual void Run() const = 0;
  virtual std::string Keyword() const = 0;
};
