#include <sstream>
#include "voiceChannel.h"

using namespace std;

VoiceChannel::VoiceChannel(string name) : Channel(name) {
}

VoiceChannel::~VoiceChannel() {
}

channelType VoiceChannel::getType() {
  return VOICE;
}

vector<Message> VoiceChannel::getMessages() {
  vector<Message> messages;
  messages.push_back(lastMessage);
  return messages;
}

/** Altera o atributo da última mensagem enviada no canal.
 * @param newMessage objeto contendo as informações da mensagem
*/
void VoiceChannel::addMessage(Message newMessage) {
  lastMessage = newMessage;
}

/** Imprime os atributos da última mensagem num objeto ostringstream e retorna sua conversão para string.
 * @param users lista de usuários para obter o nome pelo id
 * @return string com as informações da última mensagem
 */
string VoiceChannel::printMessages(vector<User> users) {
  if (lastMessage.getContent().length() > 0) {
    ostringstream output;

    string name = users[lastMessage.getSentBy() - 1].getName();
    string date = lastMessage.getDateTime();
    string content = lastMessage.getContent();

    output << name << "<" << date << ">: " << content << endl;

    return output.str();
  }
  return "Sem mensagens para exibir"; 
}
