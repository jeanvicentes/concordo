#include "system.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

/* COMANDOS */
string System::quit() {
  return "Saindo...";
}

/** Cria um novo usuário com as informações passadas por parâmetro e retorna uma mensagem.
 * @param email email inserido.
 * @param password senha inserida.
 * @param name nome inserido.
 * @return uma mensagem de sucesso ou informando que o email já existe.
*/
string System::create_user (const string email, const string password, const string name) {
  vector<User>::iterator it = users.begin();
  // Verifica se já existe usuário cadastrado com esse email
  while (it != users.end()) {
    if (it->getEmail() == email) {
      return "Usuário já existe!";
    }

    it++;
  }
  // Gera um id automaticamente conforme o tamanho do vetor
  int id = users.size() + 1;

  // Cria o novo usuário e adiciona ao final do vetor
  User newUser(id, name, email, password);
  users.push_back(newUser);

  return "Usuário criado";
}

/** Altera a variável que armazena o id do usuário logado, caso exista um cadastrado com o email e a senha passados por parametro.
 * @param email email inserido.
 * @param password senha inserida.
 * @return uma mensagem de sucesso ou informando que as credenciais são inválidas.
*/
string System::login(const string email, const string password) {
  vector<User>::iterator it = users.begin();
  // Verifica se existe usuário com esse email e senha
  while (it != users.end()) {
    if (it->getEmail() == email) {
      if (it->getPassword() == password) {
        // Informa ao sistema o id do usuário logado
        loggedUserId = it->getId();
        return "Logado com " + email;
      }
    }

    it++;
  }

  return "Senha ou usuário inválidos!";
}

/** Altera a variável que armazena o id do usuário logado para 0, caso exista um usuário logado.
 * @return uma mensagem de sucesso ou informando que não há nenhum conectado.
*/
string System::disconnect() {
  // Verifica se existe usuario logado
  if (loggedUserId == 0) {
    return "Não está conectado";
  }
  vector<User>::iterator it;
  // Obtem o usuario logado pelo id
  int targetId = loggedUserId;
  it = find_if(users.begin(), users.end(), [targetId](User user) {
    return targetId == user.getId();
  });

  // Desconecta o usuário atual
  loggedUserId = 0;

  // Reseta o servidor e canal que ele estava visualizando
  connectedServerName = "";
  connectedChannelName = "";

  return "Desconectando usuário " + it->getEmail();
}

/** Cria um novo servidor com o nome passado por parâmetro (caso não exista nenhum com o mesmo nome) e retorna uma mensagem.
 * @param name nome inserido.
 * @return uma mensagem de sucesso ou informando que o servidor já existe, ou não há usuário conectado.
*/
string System::create_server(const string name) {
  // Verifica se existe usuario logado
  if (loggedUserId == 0) {
    return "Não está conectado";
  }
  vector<Server>::iterator it;
  // Verifica se já existe um servidor com esse nome
  it = find_if(servers.begin(), servers.end(), [name](Server server) {
    return name == server.getName();
  });
  if (it != servers.end()) {
    return "Servidor com esse nome já existe";
  }

  // Cria um novo servidor e adiciona ao final do vector
  Server newServer(loggedUserId, name);
  servers.push_back(newServer);

  return "Servidor criado";
}

/** Altera a descrição do servidor passado por parâmetro, caso o usuário logado seja o dono, e retorna uma mensagem.
 * @param name nome do servidor.
 * @param description descrição inserida.
 * @return uma mensagem de sucesso ou informando que o servidor não existe, ou não há usuário conectado, ou ele não possui permissão.
*/
string System::set_server_desc(const string name, const string description) {
  // Verifica se existe usuario logado
  if (loggedUserId == 0) {
    return "Não está conectado";
  }
  vector<Server>::iterator it;
  // Verifica se existe um servidor com esse nome
  it = find_if(servers.begin(), servers.end(), [name](Server server) {
    return name == server.getName();
  });
  if (it == servers.end()) {
    return "Servidor '" + name + "' não encontrado";
  }
  // Verifica se o usuário logado é o dono
  if (it->getOwner() != loggedUserId) {
    return "Você não pode alterar a descrição de um servidor que não foi criado por você";
  }

  // Caso esteja tudo ok, altera a descrição
  it->setDescription(description);
  return "Descrição do servidor '" + name + "' modificada!";
}

/** Adiciona um código de convite a um servidor, ou o remove caso o parâmetro seja uma string vazia.
 * @param name nome do servidor.
 * @param code código de convite inserido ou string vazia.
 * @return uma mensagem de sucesso ou informando que o servidor não existe, ou não há usuário conectado, ou ele não possui permissão.
*/
string System::set_server_invite_code(const string name, const string code) {
  // Verifica se existe usuario logado
  if (loggedUserId == 0) {
    return "Não está conectado";
  }
  vector<Server>::iterator it;
  // Verifica se existe um servidor com esse nome
  it = find_if(servers.begin(), servers.end(), [name](Server server) {
    return name == server.getName();
  });
  if (it == servers.end()) {
    return "Servidor '" + name + "' não encontrado";
  }
  // Verifica se o usuário logado é o dono
  if (it->getOwner() != loggedUserId) {
    return "Você não pode alterar o código de convite de um servidor que não foi criado por você";
  }
  // Se está tudo ok e foi passado um código
  if (code.length() > 0) {
    it->setInvitationCode(code);
    return "Código de convite do servidor '" + name +"' modificado!";
  }
  // Caso não tenha um código no comando
  it->setInvitationCode("");
  return "Código de convite do servidor '" + name +"' removido!";
}

/** Percorre a lista de servidores imprimindo seus nomes num objeto ostringstream e retorna a conversão para string.
 * @return uma string contendo a lista de todos os servidores do sistema.
*/
string System::list_servers() {
  // Verifica se existe usuario logado
  if (loggedUserId == 0) {
    return "Não está conectado";
  }

  vector<Server>::iterator it = servers.begin();
  ostringstream output;

  // Percorre o vector redirecionando os nomes dos servidores para o objeto de saída
  output << it->getName();
  ++it;
  while (it != servers.end()) {
    output << endl << it->getName();
    ++it;
  }

  // Retorna o objeto ostringstream convertido para string
  return output.str();
}

/** Recebe um nome de um servidor por parâmetro e o remove do vector, caso ele exista e o usuário logado seja o dono dele.
 * @param name nome do servidor.
 * @return uma mensagem de sucesso ou informando que o servidor não existe, ou não há usuário conectado, ou ele não possui permissão.
*/
string System::remove_server(const string name) {
  // Verifica se existe usuario logado
  if (loggedUserId == 0) {
    return "Não está conectado";
  }
  vector<Server>::iterator it;
  // Verifica se existe um servidor com esse nome
  it = find_if(servers.begin(), servers.end(), [name](Server server) {
    return name == server.getName();
  });
  if (it == servers.end()) {
    return "Servidor '" + name + "' não encontrado";
  }
  // Verifica se o usuário logado é o dono
  if (it->getOwner() != loggedUserId) {
    return "Você não é dono(a) do servidor '" + name + "'";
  }
  // Se estiver tudo ok, remove o servidor do vector
  servers.erase(it);

  return "Servidor '" + name + "' removido";
}

/** Adiciona o id do usuário na lista de membros do servidor caso ele tenha inserido o código de convite correto, ou não tenha código, ou seja o dono.
 * @param name nome do servidor.
 * @param code código inserido pelo usuário.
 * @return uma mensagem de sucesso ou informando que o servidor não existe, ou não há usuário conectado, ou ele não possui permissão.
*/
string System::enter_server(const string name, const string code) {
  // Verifica se existe usuario logado
  if (loggedUserId == 0) {
    return "Não está conectado";
  }
  vector<Server>::iterator it;
  // Verifica se existe um servidor com esse nome
  it = find_if(servers.begin(), servers.end(), [name](Server server) {
    return name == server.getName();
  });
  if (it == servers.end()) {
    return "Servidor '" + name + "' não encontrado";
  }
  // Verifica se o usuário logado não é o dono
  if (it->getOwner() != loggedUserId) {
    // Verifica se possui código de convite
    if (it->getInvitationCode().length() > 0) {
      // Verifica se o código está errado
      if (code != it->getInvitationCode()) {
        return "Servidor requer código de convite";
      }
    }
  }
  // Caso tudo ok, adiciona no servidor
  connectedServerName = name;
  it->addMember(loggedUserId);
  return "Entrou no servidor com sucesso";
}

/** Reseta a propriedade que armazena o nome do servidor visualizado no momento.
 * @return uma mensagem de sucesso ou informando que não há servidor visualizado no momento, ou não há usuário conectado.
*/
string System::leave_server() {
  // Verifica se existe usuario logado
  if (loggedUserId == 0) {
    return "Não está conectado";
  }
  // Verifica se está vendo algum servidor
  if (connectedServerName.length() == 0) {
    return "Você não está visualizando nenhum servidor";
  }
  
  // Caso tudo ok, desconecta o usuário do servidor atual
  string temp = connectedServerName;
  connectedServerName = "";
  return "Saindo do servidor '" + temp + "'";
}

/** Percorre a lista de participantes do servidor atual imprimindo seus nomes num objeto ostringstream e retorna a conversão para string.
 * @return uma string contendo a lista de todos os participantes do servidor.
*/
string System::list_participants() {
  // Verifica se existe usuario logado
  if (loggedUserId == 0) {
    return "Não está conectado";
  }
  // Verifica se está vendo algum servidor
  if (connectedServerName.length() == 0) {
    return "Você não está visualizando nenhum servidor";
  }

  // Obtém o servidor na lista pelo nome
  string name = connectedServerName;
  auto target = find_if(servers.begin(), servers.end(), [name](Server server) {
    return name == server.getName();
  });

  // Obtém a lista de ids dos membros
  vector<int> members = target->getMemberIds();

  ostringstream output;
  output << "Membros de '" + name + "':" << endl;
  // Percorre a lista de membros do servidor acessando os nomes na lista de usuários do sistema
  auto it = members.begin();
  output << users[*it - 1].getName();
  ++it;
  while (it != members.end()) {
    output << endl << users[*it - 1].getName();
    ++it;
  }
  
  // Retorna o objeto ostringstream convertido para string
  return output.str();
}

/** Percorre a lista de canais do servidor imprimindo seus nomes num objeto ostringstream e retorna a conversão para string.
 * @return uma string contendo a lista de todos os canais de texto e voz do servidor.
*/
string System::list_channels() {
  // Verifica se existe usuario logado
  if (loggedUserId == 0) {
    return "Não está conectado";
  }
  // Verifica se está vendo algum servidor
  if (connectedServerName.length() == 0) {
    return "Você não está visualizando nenhum servidor";
  }

  // Obtém o servidor na lista pelo nome
  string serverName = connectedServerName;
  auto target = find_if(servers.begin(), servers.end(), [serverName](Server server) {
    return serverName == server.getName();
  });

  // Obtém a lista de canais
  vector<Channel*> channels = target->getChannels();

  ostringstream outputT;
  ostringstream outputV;

  // Imprime os canais de texto e voz nas suas respectivas saidas 
  outputT << "#canais de texto";
  outputV << "#canais de voz";
  auto it = channels.begin();
  while (it != channels.end()) {
    if ((*it)->getType() == TEXT) {
      outputT << endl << (*it)->getName();
    } else {
      outputV << endl << (*it)->getName();
    }
    ++it;
  }

  // Reune os dois numa unica saída
  outputT << endl << outputV.str();
  // Retorna o objeto ostringstream convertido para string
  return outputT.str();
}

/** Cria um novo canal com o nome e tipo passados por parâmetro e adiciona na lista de canais do servidor atual.
 * @param name nome do canal.
 * @param type tipo do canal (texto ou voz).
 * @return uma mensagem de sucesso ou informando que não há servidor visualizado no momento, ou não há usuário conectado, ou o canal já existe.
*/
string System::create_channel(const string name, const string type) {
  // Verifica se existe usuario logado
  if (loggedUserId == 0) {
    return "Não está conectado";
  }
  // Verifica se está vendo algum servidor
  if (connectedServerName.length() == 0) {
    return "Você não está visualizando nenhum servidor";
  }

  // Obtém o servidor na lista pelo nome
  string serverName = connectedServerName;
  auto target = find_if(servers.begin(), servers.end(), [serverName](Server server) {
    return serverName == server.getName();
  });

  // Obtém a lista de canais
  vector<Channel*> channels = target->getChannels();

  // Percorre a lista verificando se existe canal com esse nome
  string targetName = name;
  channelType targetType = type == "texto" ? TEXT : VOICE;
  auto it = find_if(channels.begin(), channels.end(), [targetName, targetType](Channel* channel) {
    return targetName == channel->getName() && targetType == channel->getType();
  });
  if (it != channels.end()) {
    return "Canal de " + type + " '" + name + "' já existe!";
  } else {
    // Cria um novo canal com o tipo escolhido
    Channel * newChannel;
    if (type == "texto") {
      newChannel = new TextChannel(name);
    } else if (type == "voz") {
      newChannel = new VoiceChannel(name);
    } else {
      return "Tipo inválido";
    }
    // Adiciona na lista do servidor
    target->addChannel(newChannel);
    return "Canal de " + type + " '" + name + "' criado";
  }
}

/** Altera a variável que guarda o canal visualizado no momento para o primeiro canal da lista com nome igual ao passado por parâmetro.
 * @param name nome do canal.
 * @return uma mensagem de sucesso ou informando que não há servidor visualizado no momento, ou não há usuário conectado, ou o canal não existe.
*/
string System::enter_channel(const string name) {
  // Verifica se existe usuario logado
  if (loggedUserId == 0) {
    return "Não está conectado";
  }
  // Verifica se está vendo algum servidor
  if (connectedServerName.length() == 0) {
    return "Você não está visualizando nenhum servidor";
  }

  // Obtém o servidor na lista pelo nome
  string serverName = connectedServerName;
  auto target = find_if(servers.begin(), servers.end(), [serverName](Server server) {
    return serverName == server.getName();
  });

  // Obtém a lista de canais do servidor
  vector<Channel*> channels = target->getChannels();

  // Percorre a lista verificando se existe canal com esse nome
  string targetName = name;
  auto it = find_if(channels.begin(), channels.end(), [targetName](Channel* channel) {
    return targetName == channel->getName();
  });
  if (it == channels.end()) {
    return "Canal '" + name + "' não existe";
  } else {
    // Guarda o canal conectado
    connectedChannelName = (*it)->getName();
  }

  return "Entrou no canal '" + name + "'";
}

/** Reseta a propriedade que armazena o nome do canal visualizado no momento.
 * @return uma mensagem de sucesso ou informando que não há canal visualizado no momento, ou não há usuário conectado.
*/
string System::leave_channel() {
  // Verifica se existe usuario logado
  if (loggedUserId == 0) {
    return "Não está conectado";
  }
  // Verifica se está vendo algum canal
  if (connectedChannelName.length() == 0) {
    return "Você não está visualizando nenhum canal";
  }
  
  // Caso tudo ok, desconecta o usuário do canal atual
  string temp = connectedChannelName;
  connectedChannelName = "";
  return "Saindo do canal '" + temp + "'";
}

string System::send_message(const string message) {
  return "send_message NÃO IMPLEMENTADO";
}

string System::list_messages() {
  return "list_messages NÃO IMPLEMENTADO";
}




/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */