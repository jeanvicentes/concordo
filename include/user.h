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

    string getName();
    string getEmail();
};

#endif