#include "textChannel.h"

TextChannel::TextChannel(string name) : Channel(name) {
}

TextChannel::~TextChannel() {
}

channelType TextChannel::getType() {
  return TEXT;
}