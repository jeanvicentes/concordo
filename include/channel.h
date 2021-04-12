#ifndef CHANNEL_H
#define CHANNEL_H
#include <iostream>
#include <vector>
#include "message.h"
#include "user.h"

enum channelType {
  TEXT,
  VOICE
};

/** Classe que representa um canal */
class Channel {
  protected:
    std::string name; /**< Nome do canal */
  public:
    Channel(std::string _name) { name = _name; } /**< Construtor parametrizado de canal */
    virtual ~Channel() {} /**< Destrutor de canal */

    std::string getName() { return name; } /**< Retorna o nome */

    virtual channelType getType() = 0; /**< Método virtual que retorna o tipo do canal */
    virtual void addMessage(Message newMessage) = 0; /**< Método virtual que adiciona uma mensagem */
    virtual std::string printMessages(std::vector<User> users) = 0; /**< Método virtual que retorna as mensagens formatadas em string */
};


#endif