#include "user.h"

/** Inicializa os atributos com valores nulos */
User::User() {
  id = 0;
  name = "";
  email = "";
  password = "";
}

/** Inicializa os atributos com os valores do parâmetro */
User::User(const int _id, const string _name, const string _email, const string _password) {
  id = _id;
  name = _name;
  email = _email;
  password = _password;
}

User::~User() {
}

int User::getId() {
  return id;
}

string User::getName() {
  return name;
}

string User::getEmail() {
  return email;
}

string User::getPassword() {
  return password;
}
