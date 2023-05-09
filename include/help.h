#include <iostream>
#include <sstream>

/**
 * @brief Help text for copy command
 * 
 * @return std::string 
 */
inline std::string CopyHelp() {
  std::stringstream text;
  text << "\u001b[36;1m";
  text << "How to use: \n";
  text << "cp [--help | -h] [-a] "
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
 * @brief Help text for move command
 * 
 * @return std::string 
 */
inline std::string MoveHelp() {
  std::stringstream text;
  text << "\u001b[36;1m";
  text << "How to use: \n";
  text << "mv [--help | -h] "
          "<input_text_file> <output_text_file>\n\n";
  text << "Arguments: \n";
  text << "Input_file: The path to the input .txt file\n";
  text << "Output_file: The path to the output .txt file\n";
  text << "Flags:\n";
  text << "-h | --help: Shows the appropiate usage of the program\n";
  text << "\u001b[0m";
  return text.str();
}
