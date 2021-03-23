#include "system.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

/* COMANDOS */
string System::quit() {
  return "Saindo...";
}

/** Cria um novo usuário com as informações passadas por parâmetro e retorna uma mensagem.
 * @param email email inserido.
 * @param password senha inserida.
 * @param name nome inserido.
 * @return uma mensagem de sucesso ou informando que o email já existe.
*/
string System::create_user (const string email, const string password, const string name) {
  vector<User>::iterator it = users.begin();
  // Verifica se já existe usuário cadastrado com esse email
  while (it != users.end()) {
    if (it->getEmail() == email) {
      return "Usuário já existe!";
    }

    it++;
  }
  // Gera um id automaticamente conforme o tamanho do vetor
  int id = users.size();

  // Cria o novo usuário e adiciona ao final do vetor
  User newUser(id, name, email, password);
  users.push_back(newUser);

  return "Usuário criado";
}

string System::login(const string email, const string password) {

  return "login NÃO IMPLEMENTADO";
}

string System::disconnect() {
  return "disconnect NÃO IMPLEMENTADO";
}

string System::create_server(const string name) {
  return "create_server NÃO IMPLEMENTADO";
}

string System::set_server_desc(const string name, const string description) {
  return "set_server_desc NÃO IMPLEMENTADO";
}

string System::set_server_invite_code(const string name, const string code) {
  return "set_server_invite_code NÃO IMPLEMENTADO";
}

string System::list_servers() {
  return "list_servers NÃO IMPLEMENTADO";
}

string System::remove_server(const string name) {
  return "remove_server NÃO IMPLEMENTADO";
}

string System::enter_server(const string name, const string code) {
  return "enter_server NÃO IMPLEMENTADO";
}

string System::leave_server() {
  return "leave_server NÃO IMPLEMENTADO";
}

string System::list_participants() {
  return "list_participants NÃO IMPLEMENTADO";
}

string System::list_channels() {
  return "list_channels NÃO IMPLEMENTADO";
}

string System::create_channel(const string name, const string type) {
  return "create_channel NÃO IMPLEMENTADO";
}

string System::enter_channel(const string name) {
  return "enter_channel NÃO IMPLEMENTADO";
}

string System::leave_channel() {
  return "leave_channel NÃO IMPLEMENTADO";
}

string System::send_message(const string message) {
  return "send_message NÃO IMPLEMENTADO";
}

string System::list_messages() {
  return "list_messages NÃO IMPLEMENTADO";
}




/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */