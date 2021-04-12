#ifndef MESSAGE_H
#define MESSAGE_H

#include <istream>

/** Classe que representa um mensagem de texto ou de voz */
class Message {
  private:
    std::string dateTime; /**< Data e hora do envio */
    int sentBy; /**< ID do usuário que enviou a mensagem */
    std::string content; /**< Conteúdo da mensagem */
  public:
    Message(); /**< Construtor da mensagem */
    Message(std::string date, int id, std::string text); /**< Construtor parametrizado da mensagem */
    ~Message(); /**< Destrutor da mensagem */

    std::string getDateTime(); /**< Retorna a data e hora de envio */
    int getSentBy(); /**< Retorna ID do usuário que enviou a mensagem */
    std::string getContent(); /**< Retorna o conteúdo da mensagem */

    Message& operator= (Message const &m); /** Sobrecarga do operador de atribuição */
};


#endif