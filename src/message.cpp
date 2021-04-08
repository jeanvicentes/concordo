#include "message.h"

using namespace std;

Message::Message() {
  content = "";
}

/** Inicializa os atributos com os valores do parâmetro */
Message::Message(string date, int id, string text) {
  dateTime = date;
  sentBy = id;
  content = text;
}

Message::~Message() {
}

string Message::getDateTime() {
  return dateTime;
}

int Message::getSentBy() {
  return sentBy;
}

string Message::getContent() {
  return content;
}

/** Copia os atributos da mensagem passada por referência para a mensagem atual
 * @param m referência de objeto do tipo Message.
 * @return referência para o objeto atual
*/
Message& Message::operator= (Message const &m) {
  dateTime = m.dateTime;
  sentBy = m.sentBy;
  content = m.content;

  return *this;
}