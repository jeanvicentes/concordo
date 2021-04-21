#include "system.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iomanip>      // std::put_time
#include <ctime>        // std::time_t, struct std::tm, std::localtime
#include <chrono>       // std::chrono::system_clock
#include <typeinfo>

using namespace std;
using std::chrono::system_clock;

/** Obtém a data e hora atual */
struct tm* currentTime() {
	time_t tt =  system_clock::to_time_t(system_clock::now());
	return localtime(&tt);
}

/** Converte string para inteiro */
int stringToInt(string s) {
  int i;
  stringstream sstream(s);
  sstream >> i;
  return i;
}

/** Percorre a lista de servidores liberando a memória alocada para os seus canais */
System::~System() {
  for (size_t i = 0; i < servers.size(); ++i) {
    vector<Channel*> channels = servers[i].getChannels();
    for (size_t j = 0; j < channels.size(); ++j) {
      delete channels[j];
    }
  }
}

/** Executa os métodos que salvam os dados nos arquivos txt */
void System::save() {
  saveUsers();
  saveServers();
}

/** Imprime no arquivo users.txt a quantidade de usuários, seguida dos atributos de cada usuário do sistema*/
void System::saveUsers() {
  ofstream userFile("users.txt");
  // Verifica se o arquivo foi aberto
  if (!userFile) {
    cerr << "O arquivo não foi aberto" << endl;
    exit(1);
  } else {
    // Imprime a quantidade de usuários
    userFile << users.size() << endl;
    // Percorre o vetor de usuários imprimindo seus atributos no arquivo
    for (auto it = users.begin(); it != users.end(); ++it) {
      userFile << it->getId() << endl;
      userFile << it->getName() << endl;
      userFile << it->getEmail() << endl;
      userFile << it->getPassword() << endl;
    }

    // Fecha o arquivo
    userFile.close();
  }
}

/** Imprime no arquivo servidores.txt as informações de cada servidor do sistema */
void System::saveServers() {
  ofstream serverFile("servers.txt");
  // Verifica se o arquivo foi aberto
  if (!serverFile) {
    cerr << "O arquivo não foi aberto" << endl;
    exit(1);
  } else {
    // Imprime a quantidade de servidores
    serverFile << servers.size() << endl;

    // Percorre o vetor de servidores
    for (auto it = servers.begin(); it != servers.end(); ++it) {
      serverFile << it->getOwner() << endl;
      serverFile << it->getName() << endl;
      serverFile << it->getDescription() << endl;
      serverFile << it->getInvitationCode() << endl;

      vector<int> memberIds = it->getMemberIds();
      serverFile << memberIds.size() << endl;
      // Imprime os ids dos usuários participantes
      for (auto id = memberIds.begin(); id != memberIds.end(); ++id) {
        serverFile << *id << endl;
      }

      vector<Channel*> channels = it->getChannels();
      serverFile << channels.size() << endl;
      // Imprime os atributos dos canais
      for (auto c = channels.begin(); c != channels.end(); ++c) {
        serverFile << (*c)->getName() << endl;
        string type = (*c)->getType() == TEXT ? "TEXTO" : "VOZ";
        serverFile << type << endl;

        // Imprime a quantidade de mensagens
        vector<Message> messages = (*c)->getMessages();
        serverFile << messages.size() << endl;
        // Imprime os atributos de cada mensagem
        for (auto m = messages.begin(); m != messages.end(); ++m) {
          serverFile << m->getSentBy() << endl;
          serverFile << m->getDateTime() << endl;
          serverFile << m->getContent() << endl;
        }
      }
    }

    // Fecha o arquivo
    serverFile.close();
  }
}

/** Executa os métodos que restauram os dados dos arquivos txt */
void System::load() {
  int fileSize = 0;
  ifstream userFile("users.txt");
  ifstream serverFile("servers.txt");

  // Verifica se o arquivo de usuários existe e não está vazio
  if (userFile) {
    userFile.seekg(0, ios::end);
    fileSize = userFile.tellg();
    if (fileSize > 0) {
      loadUsers();
    }

    // Fecha o arquivo
    userFile.close();
  }
  // Verifica se o arquivo de servidores existe e não está vazio
  if (serverFile) {
    serverFile.seekg(0, ios::end);
    fileSize = serverFile.tellg();
    if (fileSize > 0) {
      loadServers();
    }

    // Fecha o arquivo
    serverFile.close();
  }
}

/** Obtém os dados do arquivo users.txt e cria usuários correspondentes no sistema */
void System::loadUsers() {
  ifstream userFile("users.txt");

  if (!userFile) {
    cerr << "O arquivo não foi aberto" << endl;
    exit(1);
  } else {
    string size, id, name, email, pass;
    size_t u;

    // Lê a quantidade de usuários e converte para size_t
    userFile >> size; 
    u = stringToInt(size);
    
    userFile.ignore();
    // Percorre o arquivo capturando os atributos dos usuários
    for (size_t i = 0; i < u ; ++i) {
      getline(userFile, id);
      getline(userFile, name);
      getline(userFile, email);
      getline(userFile, pass);

      // Converter a string id para int
      int intId = stringToInt(id);
      
      // Verifica se o usuário já existe
      auto it = find_if(users.begin(), users.end(), [intId](User user) {
        return intId == user.getId();
      });
      // Cria um novo usuário e adiciona na lista
      if (it == users.end()) {
        User newUser(intId, name, email, pass);
        users.push_back(newUser);
      }
    }

    // Fecha o arquivo
    userFile.close();
  }

}

/** Obtém os dados do arquivo servers.txt e cria servidores correspondentes no sistema */
void System::loadServers() {
  ifstream serverFile("servers.txt");

  if (!serverFile) {
    cerr << "O arquivo não foi aberto" << endl;
    exit(1);
  } else {
    string size, id, name, desc, code, channelName, channelType, date, text;
    size_t s, u, c, m;

    // Reseta o vector de servers
    servers.clear();

    // Lê a quantidade de servidores e converte para size_t
    serverFile >> size; 
    s = stringToInt(size);
    
    serverFile.ignore();
    // Percorre o arquivo capturando os atributos dos servidores
    for (size_t i = 0; i < s; i++) {
      getline(serverFile, id);
      getline(serverFile, name);
      getline(serverFile, desc);
      getline(serverFile, code);

      // Converte a string id para int
      int intId = stringToInt(id);
      
      // Cria um novo servidor e seta os atributos
      Server newServer(intId, name);
      newServer.setDescription(desc);
      if (code.length() > 0) {
        newServer.setInvitationCode(code);
      } else {
        newServer.setInvitationCode("");
      }

      // Obtém a quantidade de usuários
      getline(serverFile, size);
      u = stringToInt(size);

      // Obtém os ids dos membros, converte para inteiro e adiciona ao servidor
      for (size_t j = 0; j < u; j++) {
        getline(serverFile, id);
        intId = stringToInt(id);
        newServer.addMember(intId);
      }

      // Obtém a quantidade de canais
      getline(serverFile, size);
      c = stringToInt(size);

      // Captura os atributos dos canais
      for (size_t j = 0; j < c; ++j) {
        getline(serverFile, channelName);
        getline(serverFile, channelType);

        // Cria um novo canal com o tipo informado
        Channel * newChannel;
        if (channelType == "TEXTO") {
          newChannel = new TextChannel(channelName);
        } else if (channelType == "VOZ") {
          newChannel = new VoiceChannel(channelName);
        }

        // Obtém a quantidade de mensagens
        getline(serverFile, size);
        m = stringToInt(size);

        // Captura os atributos das mensagens
        for (size_t k = 0; k < m; ++k) {
          // Obtém o id de quem enviou e converte para int
          getline(serverFile, id);
          intId = stringToInt(id);

          getline(serverFile, date);
          getline(serverFile, text);

          // Cria a nova mensagem e adiciona ao canal
          Message newMessage(date, intId, text);
          newChannel->addMessage(newMessage);
        }

        // Adiciona o canal ao servidor
        newServer.addChannel(newChannel);
      }
      // Adiciona o servidor na lista
      servers.push_back(newServer);
    }
    // Fecha o arquivo
    serverFile.close();
  }
}

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
  load(); 
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
  save();
  return "Usuário criado";
}

/** Altera a variável que armazena o id do usuário logado, caso exista um cadastrado com o email e a senha passados por parametro.
 * @param email email inserido.
 * @param password senha inserida.
 * @return uma mensagem de sucesso ou informando que as credenciais são inválidas.
*/
string System::login(const string email, const string password) {
  load();
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
  load(); 
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
  save();
  return "Servidor criado";
}

/** Altera a descrição do servidor passado por parâmetro, caso o usuário logado seja o dono, e retorna uma mensagem.
 * @param name nome do servidor.
 * @param description descrição inserida.
 * @return uma mensagem de sucesso ou informando que o servidor não existe, ou não há usuário conectado, ou ele não possui permissão.
*/
string System::set_server_desc(const string name, const string description) {
  load(); 
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
  save();
  return "Descrição do servidor '" + name + "' modificada!";
}

/** Adiciona um código de convite a um servidor, ou o remove caso o parâmetro seja uma string vazia.
 * @param name nome do servidor.
 * @param code código de convite inserido ou string vazia.
 * @return uma mensagem de sucesso ou informando que o servidor não existe, ou não há usuário conectado, ou ele não possui permissão.
*/
string System::set_server_invite_code(const string name, const string code) {
  load(); 
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
    save();
    return "Código de convite do servidor '" + name +"' modificado!";
  }
  // Caso não tenha um código no comando
  it->setInvitationCode("");
  save();
  return "Código de convite do servidor '" + name +"' removido!";
}

/** Percorre a lista de servidores imprimindo seus nomes num objeto ostringstream e retorna a conversão para string.
 * @return uma string contendo a lista de todos os servidores do sistema.
*/
string System::list_servers() {
  load();
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
  load();
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
  save();
  return "Servidor '" + name + "' removido";
}

/** Adiciona o id do usuário na lista de membros do servidor caso ele tenha inserido o código de convite correto, ou não tenha código, ou seja o dono.
 * @param name nome do servidor.
 * @param code código inserido pelo usuário.
 * @return uma mensagem de sucesso ou informando que o servidor não existe, ou não há usuário conectado, ou ele não possui permissão.
*/
string System::enter_server(const string name, const string code) {
  load();
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
  save();
  return "Entrou no servidor com sucesso";
}

/** Reseta a propriedade que armazena o nome do servidor visualizado no momento.
 * @return uma mensagem de sucesso ou informando que não há servidor visualizado no momento, ou não há usuário conectado.
*/
string System::leave_server() {
  load();
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
  load();
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
  load(); 
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
  load(); 
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
    save();
    return "Canal de " + type + " '" + name + "' criado";
  }
}

/** Altera a variável que guarda o canal visualizado no momento para o primeiro canal da lista com nome igual ao passado por parâmetro.
 * @param name nome do canal.
 * @return uma mensagem de sucesso ou informando que não há servidor visualizado no momento, ou não há usuário conectado, ou o canal não existe.
*/
string System::enter_channel(const string name) {
  load(); 
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
  load();
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

/** Cria uma nova mensagem com o conteúdo passado, o id do usuário que enviou e a hora-data e adiciona ao canal atual.
 * @param message conteúdo da mensagem inserida pelo usuário
*/
string System::send_message(const string message) {
  load(); 
  // Verifica se existe usuario logado
  if (loggedUserId == 0) {
    return "Não está conectado";
  }
  // Verifica se está vendo algum servidor
  if (connectedServerName.length() == 0) {
    return "Você não está visualizando nenhum servidor";
  }
  // Verifica se está vendo algum canal
  if (connectedChannelName.length() == 0) {
    return "Você não está visualizando nenhum canal";
  }

  // Caso tudo ok, cria uma nova mensagem com os atributos
  ostringstream dateTime; 
  dateTime << put_time(currentTime(), "%H:%M - %d/%m/%Y");
  Message newMessage(dateTime.str(), loggedUserId, message);

  // Obtém o servidor na lista pelo nome
  string serverName = connectedServerName;
  auto server = find_if(servers.begin(), servers.end(), [serverName](Server server) {
    return serverName == server.getName();
  });

  // Obtém a lista de canais do servidor
  vector<Channel*> channels = server->getChannels();

  // Obtém o primeiro canal de mesmo nome na lista
  string channelName = connectedChannelName;
  auto channel = find_if(channels.begin(), channels.end(), [channelName](Channel* channel) {
    return channelName == channel->getName();
  });

  // Adiciona a nova mensagem ao canal
  (*channel)->addMessage(newMessage);
  save();
  return "Mensagem enviada";
}

/** Obtém o primeiro canal na lista de nome igual ao canal conectado e lista suas mensagens exibindo o nome de quem enviou, a data e hora e o conteúdo.
 * @return uma string contendo a lista de todas as mensagens do canal, se for de texto, ou a última mensagem do canal de voz.
*/
string System::list_messages() {
  load(); 
  // Verifica se existe usuario logado
  if (loggedUserId == 0) {
    return "Não está conectado";
  }
  // Verifica se está vendo algum servidor
  if (connectedServerName.length() == 0) {
    return "Você não está visualizando nenhum servidor";
  }
  // Verifica se está vendo algum canal
  if (connectedChannelName.length() == 0) {
    return "Você não está visualizando nenhum canal";
  }

  // Caso tudo ok, obtém o servidor na lista pelo nome
  string serverName = connectedServerName;
  auto server = find_if(servers.begin(), servers.end(), [serverName](Server server) {
    return serverName == server.getName();
  });

  // Obtém a lista de canais do servidor
  vector<Channel*> channels = server->getChannels();

  // Obtém o primeiro canal de mesmo nome na lista
  string channelName = connectedChannelName;
  auto channel = find_if(channels.begin(), channels.end(), [channelName](Channel* channel) {
    return channelName == channel->getName();
  });

  // Retorna a lista de mensagens do canal
  return (*channel)->printMessages(users);
}
