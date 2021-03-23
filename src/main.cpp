#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "system.h"
#include "executor.h"
#include "user.h"

using namespace std;

int main() {
  // inicialização do sistema
  System system;
  Executor executor(system);

  // o executor recebe o cin e o cout. Ele irá os utilizar para ler as linhas
  // de comando, executar o método correto em "sistema" e exibir as mensagens
  executor.start(cin, cout);

  return 0;
}