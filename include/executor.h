#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "system.h"
#include <istream>
#include <ostream>
#include <sstream>

using namespace std;

class Executor {
  private:
  System * system;
  stringstream ss;
  bool quit = false;

  public:
  Executor(System &system);

  void start(istream &in, ostream &out);

  string processLine(string line);
};

#endif