#include "voiceChannel.h"

VoiceChannel::VoiceChannel(string name) : Channel(name) {
}

VoiceChannel::~VoiceChannel() {
}

channelType VoiceChannel::getType() {
  return VOICE;
}