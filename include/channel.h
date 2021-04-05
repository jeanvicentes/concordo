#ifndef CHANNEL_H
#define CHANNEL_H
#include <iostream>

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
    ~Channel(); /**< Destrutor de canal */

    virtual channelType getType() = 0; /**< Método virtual que retorna o tipo do canal */
};


#endif