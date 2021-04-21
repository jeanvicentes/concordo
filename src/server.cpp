#include "server.h"
#include <algorithm>

using namespace std;

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

string Server::getDescription() {
  return description;
}

string Server::getInvitationCode() {
  return invitationCode;
}

vector<int> Server::getMemberIds() {
  return memberIds;
}

vector<Channel*> Server::getChannels() {
  return channels;
}

void Server::setDescription(const string desc) {
  description = desc;
}

void Server::setInvitationCode(const string code) {
  invitationCode = code;
}

/** Adiciona ao final da lista de membros o ID passado por parâmetro, caso ele não esteja na lista
 * @param id id do novo membro.
*/
void Server::addMember(const int id) {
  vector<int>::iterator it;
  it = find(memberIds.begin(), memberIds.end(), id);
  if (it == memberIds.end()) {
    memberIds.push_back(id);
  }
}

/** Adiciona ao final da lista de canais o ponteiro para o canal passado por parâmetro
 * @param newChannel ponteiro para canal.
*/
void Server::addChannel(Channel* newChannel) {
  channels.push_back(newChannel);
}