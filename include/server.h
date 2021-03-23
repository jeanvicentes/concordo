#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

/** Classe que representa um servidor */
class Server {
  private:
    int ownerId; /**< ID do dono do servidor */
    string name; /**< Nome do servidor */
    string description; /**< Descrição do servidor */
    string invitationCode; /**< Código de convite necessário para entrar no servidor */
    // precisa guardar um vector de canais
    vector<int> memberIds; /**< Lista de IDs de usuários que estão no servidor */
  public:
    Server(); /**< Construtor do servidor */
    Server(int _ownerId, string _name);  /**< Construtor parametrizado do servidor */
    ~Server(); /**< Destrutor do servidor */

    int getOwner(); /**< Obtém o ID do dono do servidor */
    string getName(); /**< Obtém o nome do servidor */
};

#endif