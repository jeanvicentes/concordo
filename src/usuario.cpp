#include "usuario.h"

Usuario::Usuario() {
  id = 0;
  nome = "";
  email = "";
  senha = "";
}

Usuario::Usuario(const int _id, const string _nome, const string _email, const string _senha) {
  id = _id;
  nome = _nome;
  email = _email;
  senha = _senha;
}

Usuario::~Usuario() {
}

string Usuario::getName() {
  return nome;
}

string Usuario::getEmail() {
  return email;
}
