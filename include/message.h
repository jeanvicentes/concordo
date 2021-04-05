#ifndef MESSAGE_H
#define MESSAGE_H

#include <istream>

using namespace std;

/** Classe que representa um mensagem de texto ou de voz */
class Message {
  private:
    string dateTime; /**< Data e hora do envio */
    int sentBy; /**< ID do usuário que enviou a mensagem */
    string content; /**< Conteúdo da mensagem */
  public:
    Message(); /**< Construtor da mensagem */
    Message(string date, int id, string text); /**< Construtor parametrizado da mensagem */
    ~Message(); /**< Destrutor da mensagem */
};


#endif