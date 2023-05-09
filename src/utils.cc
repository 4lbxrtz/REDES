// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Sistemas Operativos
// Curso: 2º
// Práctica 2: Programación de aplicaciones
// Autor: Alberto Oria Martín
// Correo: alu0101415598@ull.edu.es
// Fecha: 12/12/2022

#include <sstream>

#include "utils.h"
#include "program.h"

namespace utils {

/**
 * @brief Returns the programs help (cyan color)
 * 
 * @return std::string 
 */
std::string HelpText() {
  std::stringstream text;
  text << "\u001b[36;1m";
  text << "How to use: \n";
  text << "Copyfile (path to the executable file) [--help | -h] [-a] "
          "<input_text_file> <output_text_file>\n\n";
  text << "Arguments: \n";
  text << "Input_file: The path to the input .txt file\n";
  text << "Output_file: The path to the output .txt file\n";
  text << "Flags:\n";
  text << "-h | --help: Shows the appropiate usage of the program\n";
  text << "-a: Preserves the original atributes in the copied file\n";
  text << "\u001b[0m";
  return text.str();
}

/**
 * @brief Returns the program errors (red color)
 * 
 * @param error
 */
void ErrorOutput(const std::exception& error) {
  std::cerr << "\u001b[31;1m" << "ERROR --> \u001b[0m" << error.what() << '\n';
  try {
    std::rethrow_if_nested(error);
  } catch(const std::exception& nested_exception) {
    ErrorOutput(nested_exception);
  }
}

void ErrorPrint(const std::string& error) {
  std::cerr << "\u001b[31;1m" << "ERROR --> \u001b[0m" << error << '\n';
}

/**
 * @brief Function that recieves different arguments through the argv in order to
 *        compute the querried operations
 * @param argc 
 * @param argv 
 */
void Run(const int argc, const char* argv[]) {
  std::vector<std::string> arguments(argv, argv + argc);
  if (argc > 4 || argc < 2) {
    std::cout << "Invalid number of arguments." << std::endl;
    std::cout << argv[1] << std::endl;
    std::cout << std::endl << HelpText();
    exit(EXIT_FAILURE);
  } else if ((arguments[1] == "--help" || arguments[1] == "-h")) {
    std::cout << HelpText() << std::endl;
    exit(EXIT_SUCCESS);
  }
  int shift = 0;
  bool preserve_all = false;
  bool move = false;
  if (argc == 4) {
    if (arguments[1] == "-a") {
      preserve_all = true;
    } else if (arguments[1] == "-m") {
      move = true;
    }
    ++shift;
  }
  std::string input_path = arguments[1 + shift];
  std::string output_path = arguments[2 + shift];
  if (move) {
    MoveFile(input_path, output_path);
    return;
  }
  Copyfile(input_path, output_path, preserve_all);
}

/**
 * @brief Splits the given string using a delimiter
 * 
 * @param input_string 
 * @param delim 
 * @return std::vector<std::string> 
 */
std::vector<std::string> Split(const std::string& input_string, const char delim) {
  std::vector<std::string> result;
  std::string token;
  std::stringstream buffer(input_string);
  while (!buffer.eof()) {
    getline(buffer, token, delim);
    result.push_back(token);
  }
  return result;
}

/**
 * @brief Splits the given string using different delimiters
 * 
 * @param input_string 
 * @param delims 
 * @return std::vector<std::string> 
 */
std::vector<std::string> Split(const std::string& input_string, const std::vector<char> delims) {
  std::vector<std::string> result;
  std::stringstream current_token;
  for (const auto& current_char : input_string) {
    bool is_separator = false;
    for (const auto& delim : delims) {
      if (current_char == delim) {
        is_separator = true;
        if (current_token.str().empty()) break;
        result.emplace_back(current_token.str());
        current_token.str(std::string());
        break;
      }
    }
    if (!is_separator) current_token << current_char;
  }
  if (!current_token.str().empty()) {
    result.emplace_back(current_token.str());
    current_token.str(std::string());
  }
  return result;
}

} // end utils namespace