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

}