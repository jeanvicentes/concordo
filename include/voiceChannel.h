#ifndef VOICE_CHANNEL_H
#define VOICE_CHANNEL_H

#include "channel.h"
#include "message.h"


/** Classe que representa um canal de voz */
class VoiceChannel : public Channel {
  private:
    Message lastMessage; /**< Última mensagem de voz */
  public:
    VoiceChannel(std::string name); /**< Construtor do canal de voz */
    ~VoiceChannel(); /**< Destrutor do canal de voz */

    channelType getType(); /**< Retorna o tipo do canal */
    std::vector<Message> getMessages(); /**< Retorna um vetor contendo a última mensagem */

    void addMessage(Message newMessage); /**< Sobrescreve o atributo com uma nova mensagem */
    std::string printMessages(std::vector<User> users); /**< Retorna a última mensagem formatada em string */
};

#endif