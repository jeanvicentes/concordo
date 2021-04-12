#ifndef USER_H
#define USER_H

#include <iostream>

/** Classe que representa um usuário do sistema */
class User {
  private:
    int id; /**< ID do usuário */
    std::string name; /**< Nome do usuário */
    std::string email; /**< Email do usuário */
    std::string password; /**< Senha do usuário */

  public:
    User(); /**< Construtor do usuário */
    User(const int _id, const std::string _name, const std::string _email, const std::string _password); /**< Construtor parametrizado do usuário */
    ~User();/**< Destrutor do usuário */

    int getId(); /**< Obtém o id do usuário */
    std::string getName(); /**< Obtém o nome do usuário */
    std::string getEmail(); /**< Obtém o email do usuário */
    std::string getPassword(); /**< Obtém a senha do usuário */
};

#endif