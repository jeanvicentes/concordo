#include "server.h"

/** Inicializa os atributos com valores nulos */
Server::Server() {
  ownerId = 0;
  name = "";
  description = "";
  invitationCode = "";
}

/** Inicializa os atributos nome e id do dono com os valores do parâmetro */
Server::Server(int _ownerId, string _name) {
  ownerId = _ownerId;
  name = _name;
  description = "";
  invitationCode = "";
}

Server::~Server() {
}

int Server::getOwner() {
  return ownerId;
}

string Server::getName() {
  return name;
}