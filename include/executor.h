#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "system.h"
#include <istream>
#include <ostream>
#include <sstream>

class Executor {
  private:
  System * system;
  std::stringstream ss;
  bool quit = false;

  public:
  Executor(System &system);

  void start(std::istream &in, std::ostream &out);

  std::string processLine(std::string line);
};

#endif