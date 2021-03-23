#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include <string>
#include <iostream>
#include "user.h"

using namespace std;

/** Classe que representa o sistema e concentra todas as operações do Concordo */
class System {
  private:
    //precisa guardar uma coleção de servidores;
    vector<User> users; /**< Coleção de usuários */
    int loggedUserId; /** se 0: não logado, caso contrário guarda o id do usuário logado */
    string connectedServerName;
    string connectedChannelName;

  public:

  string quit();
  string create_user (const string email, const string password, const string name);
  string login(const string email, const string password);
  string disconnect();
  string create_server(const string name);
  string set_server_desc(const string name, const string description);
  string set_server_invite_code(const string name, const string code);
  string list_servers();
  string remove_server(const string name);
  string enter_server(const string name, const string code);
  string leave_server();
  string list_participants();
  string list_channels();
  string create_channel(const string name, const string type);
  string enter_channel(const string name);
  string leave_channel();
  string send_message(const string message);
  string list_messages();
};

#endif