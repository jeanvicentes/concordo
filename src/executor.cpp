#include "executor.h"
#include <istream>
#include <ostream>
#include <iostream>
#include <sstream>
#include <queue>

using namespace std;

// Função de apoio que recebe um istringstream e
// ler todo texto restante até o fim da linha
string restOf(istringstream &ss) {
  string rest;
  getline(ss, rest, '\0'); // ler o resto da linha
  if (rest != "" && (rest[0] == ' ' || rest[0] == '\t')) {
    rest = rest.substr(1); // o primeiro caractere é um espaço, descartar
  }
  return rest;
}

// Construtor. Recebe uma referência ao sistema que vai operar
// Guarda o seu endereço para executar as operações.
Executor::Executor(System &system) {
  this->quit = false;
  this->system = &system;
}

// Inicia o processamento dos comentos.
// Esse método recebe por exemplo o "cin" e o "cout" no main
// Dessa forma ele faz o necessário para ler 1 comando por linha e
// o processar corretamente, colocando no stream de saída o resultado de cada um.
void Executor::start(istream &inputStream, ostream &outputStream) {
  string line, output;
  this->quit = false;
  while (! this->quit)
  {
    if (std::getline(inputStream, line)) {
      output = processLine(line);
      outputStream << output << endl;
    }
  }
}

// Método responsável por processar cada linha, capturando o nome do comando
// e seus parâmetros em variáveis e executar o método correspondente no sistema
string Executor::processLine(string line) {
  istringstream buf(line);
  string commandName;
  buf >> commandName;

  if (commandName.empty()) {
    return "Comando Inválido <vazio>";
  }

  if (commandName == "quit" ) {
    this->quit = true;
    return system->quit();
  }

  else if (commandName == "create-user") {
    string email, password, name;
    buf >> email;
    buf >> password;
    name = restOf(buf);
    return system->create_user(email, password, name);
  }

  else if (commandName == "login") {
    string email, password;
    buf >> email;
    buf >> password;
    return system->login(email, password);
  }

  else if (commandName == "disconnect") {
    return system->disconnect();
  }

  else if (commandName == "create-server") {
    string name;
    buf >> name;
    return system->create_server(name);
  }

  else if (commandName == "set-server-desc") {
    string name, description;
    buf >> name;
    description = restOf(buf);;
    return system->set_server_desc(name, description);
  }

  else if (commandName == "set-server-invite-code") {
    string name, code;
    buf >> name;
    buf >> code;
    return system->set_server_invite_code(name, code);
  }

  else if (commandName == "list-servers") {
    return system->list_servers();
  }

  else if (commandName == "remove-server") {
    string name;
    buf >> name;
    return system->remove_server(name);
  }

  else if (commandName == "enter-server") {
    string name, code;
    buf >> name;
    buf >> code;
    return system->enter_server(name, code);
  }

  else if (commandName == "leave-server") {
    return system->leave_server();
  }

  else if (commandName == "list-participants") {
    return system->list_participants();
  }

  else if (commandName == "list-channels") {
    return system->list_channels();
  }

  else if (commandName == "create-channel") {
    string name, type;
    buf >> name;
    buf >> type;
    return system->create_channel(name, type);
  }

  else if (commandName == "enter-channel") {
    string name;
    buf >> name;
    return system->enter_channel(name);
  }

  else if (commandName == "leave-channel") {
    return system->leave_channel();
  }
  
  else if (commandName == "send-message") {
    string message;
    message = restOf(buf);
    return system->send_message(message);
  }
  
  else if (commandName == "list-messages") {
    return system->list_messages();
  }

  else {
    return "Comando não reconhecido [" + commandName + "]";
  }
}



