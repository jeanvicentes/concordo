#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>

using namespace std;

/** Classe que representa uma usuário do sistema */
class Usuario {
  private:
    int id; /**< ID do usuário */
    string nome; /**< Nome do usuário */
    string email; /**< Email do usuário */
    string senha; /**< Senha do usuário */

  public:
    Usuario(); /**< Construtor do usuário */
    Usuario(const int _id, const string _nome, const string _email, const string _senha); /**< Construtor parametrizado do usuário */
    ~Usuario();/**< Destrutor do usuário */

    string getName();
    string getEmail();
};

#endif