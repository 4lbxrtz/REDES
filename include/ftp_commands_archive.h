#pragma once

#include <iostream>
#include <vector>
#include <optional>
#include <map>
#include <functional>

#include "ftp_command.h"


class FTPCommandsArchive {
 public:
  FTPCommandsArchive() { }

  inline FTPCommandsArchive& Record(const FTPCommand* command) {
    commands_map_.emplace(command->Keyword(), command);
    return *this;
  }
 
  inline bool Exists(const std::string& input_command) const {
    return commands_map_.count(input_command);
  }

  inline bool Execute(const std::string& input) const {
    if (Exists(input)) {
      commands_map_.at(input)->Run();
      return true;
    }
    return false;
  }

 private:
  std::map<std::string, FTPCommand*> commands_map_;  
};
