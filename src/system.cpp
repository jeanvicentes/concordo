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
  int id = users.size() + 1;

  // Cria o novo usuário e adiciona ao final do vetor
  User newUser(id, name, email, password);
  users.push_back(newUser);

  return "Usuário criado";
}

/** Altera a variável que armazena o id do usuário logado, caso exista um cadastrado com o email e a senha passados por parametro.
 * @param email email inserido.
 * @param password senha inserida.
 * @return uma mensagem de sucesso ou informando que as credenciais são inválidas.
*/
string System::login(const string email, const string password) {
  vector<User>::iterator it = users.begin();
  // Verifica se existe usuário com esse email e senha
  while (it != users.end()) {
    if (it->getEmail() == email) {
      if (it->getPassword() == password) {
        // Informa ao sistema o id do usuário logado
        loggedUserId = it->getId();
        return "Logado com " + email;
      }
    }

    it++;
  }

  return "Senha ou usuário inválidos!";
}

/** Altera a variável que armazena o id do usuário logado para 0, caso exista um usuário logado.
 * @return uma mensagem de sucesso ou informando que não há nenhum conectado.
*/
string System::disconnect() {
  // Verifica se existe usuario logado
  if (loggedUserId == 0) {
    return "Não está conectado";
  }
  vector<User>::iterator it;
  // Obtem o usuario logado pelo id
  int targetId = loggedUserId;
  it = find_if(users.begin(), users.end(), [targetId](User user) {
    return targetId == user.getId();
  });

  // Desconecta o usuário atual
  loggedUserId = 0;

  return "Desconectando usuário " + it->getEmail();
}

/** Cria um novo servidor com o nome passado por parâmetro (caso não exista nenhum com o mesmo nome) e retorna uma mensagem.
 * @param name nome inserido.
 * @return uma mensagem de sucesso ou informando que o servidor já existe, ou não há usuário conectado.
*/
string System::create_server(const string name) {
  // Verifica se existe usuario logado
  if (loggedUserId == 0) {
    return "Não está conectado";
  }
  vector<Server>::iterator it;
  // Verifica se já existe um servidor com esse nome
  it = find_if(servers.begin(), servers.end(), [name](Server server) {
    return name == server.getName();
  });
  if (it != servers.end()) {
    return "Servidor com esse nome já existe";
  }

  // Cria um novo servidor e adiciona ao final do vector
  Server newServer(loggedUserId, name);
  servers.push_back(newServer);

  return "Servidor criado";
}

/** Altera a descrição do servidor passado por parâmetro, caso o usuário logado seja o dono, e retorna uma mensagem.
 * @param name nome do servidor.
 * @param description descrição inserida.
 * @return uma mensagem de sucesso ou informando que o servidor não existe, ou não há usuário conectado, ou ele não possui permissão.
*/
string System::set_server_desc(const string name, const string description) {
  // Verifica se existe usuario logado
  if (loggedUserId == 0) {
    return "Não está conectado";
  }
  vector<Server>::iterator it;
  // Verifica se existe um servidor com esse nome
  it = find_if(servers.begin(), servers.end(), [name](Server server) {
    return name == server.getName();
  });
  if (it == servers.end()) {
    return "Servidor '" + name + "' não existe";
  }
  // Verifica se o usuário logado é o dono
  if (it->getOwner() != loggedUserId) {
    return "Você não pode alterar a descrição de um servidor que não foi criado por você";
  }

  // Caso esteja tudo ok, altera a descrição
  it->setDescription(description);
  return "Descrição do servidor '" + name + "' modificada!";
}

/** Adiciona um código de convite a um servidor, ou o remove caso o parâmetro seja uma string vazia.
 * @param name nome do servidor.
 * @param code código de convite inserido ou string vazia.
 * @return uma mensagem de sucesso ou informando que o servidor não existe, ou não há usuário conectado, ou ele não possui permissão.
*/
string System::set_server_invite_code(const string name, const string code) {
  // Verifica se existe usuario logado
  if (loggedUserId == 0) {
    return "Não está conectado";
  }
  vector<Server>::iterator it;
  // Verifica se existe um servidor com esse nome
  it = find_if(servers.begin(), servers.end(), [name](Server server) {
    return name == server.getName();
  });
  if (it == servers.end()) {
    return "Servidor '" + name + "' não existe";
  }
  // Verifica se o usuário logado é o dono
  if (it->getOwner() != loggedUserId) {
    return "Você não pode alterar o código de convite de um servidor que não foi criado por você";
  }
  // Se está tudo ok e foi passado um código
  if (code.length() > 0) {
    it->setInvitationCode(code);
    return "Código de convite do servidor '" + name +"' modificado!";
  }
  // Caso não tenha um código no comando
  it->setInvitationCode("");
  return "Código de convite do servidor '" + name +"' removido!";
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