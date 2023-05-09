// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Sistemas Operativos
// Curso: 2º
// Práctica 2: Programación de aplicaciones
// Autor: Alberto Oria Martín
// Correo: alu0101415598@ull.edu.es
// Fecha: 12/12/2022

#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <pwd.h>
#include <unistd.h>
#include <climits>

namespace utils {

std::string HelpText();

void ErrorOutput(const std::exception& error);
void ErrorPrint(const std::string& error);

void Run(const int argc, const char* argv[]);

std::vector<std::string> Split(const std::string& input_string, const char delim = ' ');
std::vector<std::string> Split(const std::string& input_string, const std::vector<char> delims);

/**
 * @brief Get the username of the logged-in user
 * 
 * @return std::string 
 */
inline std::string GetLogin() {
  return getpwuid(getuid())->pw_name;
}

/**
 * @brief Get the Hostname
 * 
 * @return std::string 
 */
inline std::string GetHostname() {
  char hostname[PATH_MAX];
  if (gethostname(hostname, PATH_MAX) == 0) return hostname;
  int error_code = errno;
  switch (error_code) {
    case EACCES:
      throw std::runtime_error("Access denied");
    case ENOMEM:
      throw std::runtime_error("Not enough memory");
    default: {
      std::stringstream error;
      error << "Unknown error" << error_code;
      throw std::runtime_error(error.str());
    }
  }
}

/**
 * @brief Get the Current Working Directory
 * 
 * @return std::string 
 */
inline std::string GetCWD() {
  char cwd[PATH_MAX];
  if (getcwd(cwd, PATH_MAX) != nullptr) return cwd;
  int error_code = errno;
  switch (error_code) {
    case EACCES:
      throw std::runtime_error("Access denied");
    case ENOMEM:
      throw std::runtime_error("Not enough memory");
    default: {
      std::stringstream error;
      error << "Unknown error" << error_code;
      throw std::runtime_error(error.str());
    }
  }
}

/**
 * @brief Get the home path of the logged-in user
 * 
 * @return std::string 
 */
inline std::string GetHome() {
  return getpwuid(getuid())->pw_dir;
}

} // end namespace Utils
