#include "sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

/* COMANDOS */
string Sistema::quit() {
  return "Saindo...";
}

/** Cria um novo usuário com as informações passadas por parâmetro e retorna uma mensagem.
 * @param email email inserido.
 * @param senha senha inserida.
 * @param nome nome inserido.
 * @return uma mensagem de sucesso ou informando que o email já existe.
*/
string Sistema::create_user (const string email, const string senha, const string nome) {
  vector<Usuario>::iterator it = usuarios.begin();
  // Verifica se já existe usuário cadastrado com esse email
  while (it != usuarios.end()) {
    if (it->getEmail() == email) {
      return "Usuário já existe!";
    }

    it++;
  }
  // Gera um id automaticamente conforme o tamanho do vetor
  int id = usuarios.size();

  // Cria o novo usuário e adiciona ao final do vetor
  Usuario novoUsuario(id, nome, email, senha);
  usuarios.push_back(novoUsuario);

  return "Usuário criado";
}

string Sistema::login(const string email, const string senha) {

  return "login NÃO IMPLEMENTADO";
}

string Sistema::disconnect() {
  return "disconnect NÃO IMPLEMENTADO";
}

string Sistema::create_server(const string nome) {
  return "create_server NÃO IMPLEMENTADO";
}

string Sistema::set_server_desc(const string nome, const string descricao) {
  return "set_server_desc NÃO IMPLEMENTADO";
}

string Sistema::set_server_invite_code(const string nome, const string codigo) {
  return "set_server_invite_code NÃO IMPLEMENTADO";
}

string Sistema::list_servers() {
  return "list_servers NÃO IMPLEMENTADO";
}

string Sistema::remove_server(const string nome) {
  return "remove_server NÃO IMPLEMENTADO";
}

string Sistema::enter_server(const string nome, const string codigo) {
  return "enter_server NÃO IMPLEMENTADO";
}

string Sistema::leave_server() {
  return "leave_server NÃO IMPLEMENTADO";
}

string Sistema::list_participants() {
  return "list_participants NÃO IMPLEMENTADO";
}

string Sistema::list_channels() {
  return "list_channels NÃO IMPLEMENTADO";
}

string Sistema::create_channel(const string nome, const string tipo) {
  return "create_channel NÃO IMPLEMENTADO";
}

string Sistema::enter_channel(const string nome) {
  return "enter_channel NÃO IMPLEMENTADO";
}

string Sistema::leave_channel() {
  return "leave_channel NÃO IMPLEMENTADO";
}

string Sistema::send_message(const string mensagem) {
  return "send_message NÃO IMPLEMENTADO";
}

string Sistema::list_messages() {
  return "list_messages NÃO IMPLEMENTADO";
}




/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */