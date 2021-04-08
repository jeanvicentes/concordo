#include <sstream>
#include "textChannel.h"

using namespace std;

TextChannel::TextChannel(string name) : Channel(name) {
}

TextChannel::~TextChannel() {
}

channelType TextChannel::getType() {
  return TEXT;
}

/** Adiciona uma nova mensagem ao fim da lista.
 * @param newMessage objeto contendo as informações da mensagem
*/
void TextChannel::addMessage(Message newMessage) {
  messages.push_back(newMessage);
}

/** Percorre a lista de mensagens imprimindo os atributos num objeto ostringstream e retorna sua conversão para string.
 * @param users lista de usuários para obter o nome pelo id
 * @return string com a lista de mensagens
 */
string TextChannel::printMessages(vector<User> users) {
  if (messages.size() > 0) {
    ostringstream output;

    for (auto it = messages.begin(); it != messages.end(); ++it) {
      string name = users[it->getSentBy() - 1].getName();
      string date = it->getDateTime();
      string content = it->getContent();

      output << name << "<" << date << ">: " << content << endl;
    }

    return output.str();
  }
  return "Sem mensagens para exibir"; 
}

