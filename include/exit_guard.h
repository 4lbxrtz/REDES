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

#include <functional>

class ExitGuard {
 public:
  ExitGuard(const std::function<void()>& on_exit_guard) : 
    on_exit_guard_(on_exit_guard) { }
  ~ExitGuard() {
    on_exit_guard_();
  }
 private:
  std::function<void()> on_exit_guard_;
};
