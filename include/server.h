#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <string>
#include <iostream>
#include "channel.h"

/** Classe que representa um servidor */
class Server {
  private:
    int ownerId; /**< ID do dono do servidor */
    std::string name; /**< Nome do servidor */
    std::string description; /**< Descrição do servidor */
    std::string invitationCode; /**< Código de convite necessário para entrar no servidor */
    std::vector<Channel*> channels; /**< Lista de ponteiros para os canais do servidor */
    std::vector<int> memberIds; /**< Lista de IDs de usuários que estão no servidor */
  public:
    Server(); /**< Construtor do servidor */
    Server(const int _ownerId, const std::string _name);  /**< Construtor parametrizado do servidor */
    ~Server(); /**< Destrutor do servidor */

    int getOwner(); /**< Obtém o ID do dono do servidor */
    std::string getName(); /**< Obtém o nome do servidor */
    std::string getDescription(); /**< Obtém a descrição do servidor */
    std::string getInvitationCode(); /**< Obtém o código de convite do servidor */
    std::vector<int> getMemberIds(); /**< Obtém a lista de IDs de usuários que estão no servidor */
    std::vector<Channel*> getChannels(); /**< Obtém a lista de ponteiros para os canais do servidor */

    void setDescription(const std::string desc); /**< Adiciona a descrição do servidor */
    void setInvitationCode(const std::string code); /**< Adiciona código de convite */
    
    void addMember(const int id); /**< Adiciona um ID de membro na lista */
    void addChannel(Channel* newChannel); /**< Adiciona um novo canal na lista */
};

#endif