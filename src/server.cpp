#include "server.h"

/** Inicializa os atributos com valores nulos */
Server::Server() {
  ownerId = 0;
  name = "";
  description = "";
  invitationCode = "";
}

/** Inicializa os atributos nome e id do dono com os valores do parâmetro */
Server::Server(const int _ownerId, const string _name) {
  ownerId = _ownerId;
  name = _name;
  description = "";
  invitationCode = "";
  memberIds.push_back(ownerId);
}

Server::~Server() {
}

int Server::getOwner() {
  return ownerId;
}

string Server::getName() {
  return name;
}

void Server::setDescription(const string desc) {
  description = desc;
}

void Server::setInvitationCode(const string code) {
  invitationCode = code;
}