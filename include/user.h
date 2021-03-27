#ifndef USER_H
#define USER_H

#include <iostream>

using namespace std;

/** Classe que representa um usuário do sistema */
class User {
  private:
    int id; /**< ID do usuário */
    string name; /**< Nome do usuário */
    string email; /**< Email do usuário */
    string password; /**< Senha do usuário */

  public:
    User(); /**< Construtor do usuário */
    User(const int _id, const string _name, const string _email, const string _password); /**< Construtor parametrizado do usuário */
    ~User();/**< Destrutor do usuário */

    int getId(); /**< Obtém o id do usuário */
    string getName(); /**< Obtém o nome do usuário */
    string getEmail(); /**< Obtém o email do usuário */
    string getPassword(); /**< Obtém a senha do usuário */
};

#endif