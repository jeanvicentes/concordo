#include "message.h"

Message::Message() {
}

/** Inicializa os atributos com os valores do parâmetro */
Message::Message(string date, int id, string text) {
  dateTime = date;
  sentBy = id;
  content = text;
}

Message::~Message() {
}