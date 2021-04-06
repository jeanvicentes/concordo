#ifndef CHANNEL_H
#define CHANNEL_H
#include <iostream>
#include "message.h"

using namespace std;

enum channelType {
  TEXT,
  VOICE
};

/** Classe que representa um canal */
class Channel {
  protected:
    string name; /**< Nome do canal */
  public:
    Channel(string _name) { name = _name; } /**< Construtor parametrizado de canal */
    ~Channel() {} /**< Destrutor de canal */

    string getName() { return name; } /**< Retorna o nome */
    virtual channelType getType() = 0; /**< Método virtual que retorna o tipo do canal */
    // virtual void addMessage(Message newMessage) = 0; /**< Método virtual que adiciona uma mensagem */
};


#endif