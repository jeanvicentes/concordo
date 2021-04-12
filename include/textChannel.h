#ifndef TEXT_CHANNEL_H
#define TEXT_CHANNEL_H

#include <vector>
#include "channel.h"
#include "message.h"

/** Classe que representa um canal de texto */
class TextChannel : public Channel {
  private:
    std::vector<Message> messages; /**< Lista de mensagens de texto */
  public:
    TextChannel(std::string name); /**< Construtor de canal de texto */
    ~TextChannel(); /**< Destrutor de canal de texto */

    channelType getType(); /**< Retorna o tipo do canal */

    void addMessage(Message newMessage); /**< Adiciona uma nova mensagem a lista */
    std::string printMessages(std::vector<User> users); /**< Retorna a lista de mensagens formatadas em string */
};

#endif