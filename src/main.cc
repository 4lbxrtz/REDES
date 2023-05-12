#include <signal.h>

#include "ftp_server.h"
#include "utility.h"

/**
 * @brief The main function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(const int argc, const char* argv[]) {
  try {
    utils::Run(argc, argv);
  } catch (const std::exception& error) {
    utils::ErrorOutput(error);
  }
  return 0;
}
