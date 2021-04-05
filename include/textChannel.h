#ifndef TEXT_CHANNEL_H
#define TEXT_CHANNEL_H

#include <vector>
#include "channel.h"
#include "message.h"

using namespace std;

/** Classe que representa um canal de texto */
class TextChannel : public Channel {
  private:
    vector<Message> messages; /**< Lista de mensagens de texto */
  public:
    TextChannel(string name); /**< Construtor de canal de texto */
    ~TextChannel(); /**< Destrutor de canal de texto */

    void addMessage(Message newMessage); /**< Adiciona uma nova mensagem a lista */
    channelType getType(); /**< Retorna o tipo do canal */
};

#endif