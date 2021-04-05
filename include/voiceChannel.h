#ifndef VOICE_CHANNEL_H
#define VOICE_CHANNEL_H

#include "channel.h"
#include "message.h"

using namespace std;

/** Classe que representa um canal de voz */
class VoiceChannel : public Channel {
  private:
    Message lastMessage; /**< Última mensagem de voz */
  public:
    VoiceChannel(string name); /**< Construtor do canal de voz */
    ~VoiceChannel(); /**< Destrutor do canal de voz */

    channelType getType(); /**< Retorna o tipo do canal */
};

#endif