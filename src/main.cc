#include <signal.h>

#include "ftp_server.h"

FTPServer *server;

extern "C" void sighandler(int signal, siginfo_t *info, void *ptr) {
  std::cout << "Dispara sigaction" << std::endl;  
  server->stop();
  exit(-1);
}

/**
 * @brief The main function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(const int argc, const char* argv[]) {
  try {
    struct sigaction action;
    action.sa_sigaction = sighandler;
    action.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &action , NULL);
    server = new FTPServer(2121);
    atexit(exit_handler);
    server->run();
  } catch (const std::exception& error) {
    utils::ErrorOutput(error);
  }
  return 0;
}
