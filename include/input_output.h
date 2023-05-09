#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <stdexcept>
#include <system_error>
#include <csignal>

/**
 * @brief Reads the standard input and returns a string
 * when Enter is pressed
 * 
 * @return std::string 
 */
inline std::string ReadLine() {
  std::vector<uint8_t> pending_input;
  while (true) {
    std::string line;
    for (const auto& byte : pending_input) {
      if (byte == '\n') {
        return line;
      }
      line.push_back(byte);
    }
    std::vector<uint8_t> buffer(1);
    ssize_t bytes_read = read(STDIN_FILENO, buffer.data() , buffer.size());
    if (bytes_read < 0) {
      throw std::system_error(errno, std::system_category());
    }
    if (bytes_read == 0) {  //  CTRL+D
      std::raise(SIGQUIT);
    }
    buffer.resize(bytes_read);
    pending_input.insert(   //  concatenates the buffer at the end of the input
      pending_input.end(),
      std::make_move_iterator(buffer.begin()),
      std::make_move_iterator(buffer.end())
    );
  }
}

/**
 * @brief Writes the given string to the standar output
 * 
 * @param output given string
 */
inline void Write(const std::string& output) {
  ssize_t bytes_written = write(STDOUT_FILENO, output.data(), output.size());
  if (bytes_written == -1) {
    throw std::runtime_error("Error while writing the output.");
  }
}

/**
 * @brief Writes the given string but adding a new line to the standar output
 * 
 * @param output given string
 */
inline void WriteLine(const std::string& output) {
  Write(output + "\n");
}
