<p align="center">
  <a href="#sobre">Sobre</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#como-rodar">Como rodar?</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#funcionalidades-e-exemplos">Funcionalidades e exemplos</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#licença-e-autora">Licença e Autora</a>
</p>

## Sobre

Concordo é um sistema em C++ similar ao Discord, operado através de comandos de uma única linha, desenvolvido como atividade 3 para a disciplina de Linguagem de Programação I do curso Bacharelado em Tecnologia da Informação.

Existe um executor que faz a interpretação dos comandos e executa o método correto no sistema.

## Como rodar?

```bash
# Clone o projeto
$ git clone https://github.com/lorenatoscano/concordo.git

# Entre na pasta
$ cd concordo

# Compile o programa
$ make

# Você pode rodar o sistema e em logo depois digitar os comandos seguidos de ENTER
$ ./concordo ou make run

# Ou pode executar o sistema redirecionando um arquivo de texto com uma lista de comandos como entrada padrão:
$ ./concordo < script_comandos.txt ou make run < script_comandos.txt
```

## Funcionalidades e exemplos
### Parte 1
Comandos relacionados a usuários e interações básicas com servidores.
#### **quit**
Encerra a aplicação. Quaisquer comandos inseridos depois disso não serão executados.

_Exemplo de entrada/saída:_
```console
quit
"Saindo..."
create-user naodeveprocessar@gmail.com naodevechegaraqui Não deve chegar aqui
```
#### **create-user**
Cadastra um novo usuário com as informações de nome, email e senha (caso não exista um usuário com o mesmo email). Gera um ID automaticamente com base no tamanho da lista de usuários do sistema.

_Exemplo de entrada/saída:_
```console
create-user monica@gmail.com sansao123 Mônica
"Usuário criado"

create-user monica@gmail.com sansao321 Mônica
"Usuário já existe!"
```
#### **login**
Caso exista no sistema um usuário com o email e a senha inseridos, efetua o seu login, ou seja, altera a variável que armazena o ID do usuário logado.

_Exemplo de entrada/saída:_
```console
login monica@gmail.com SENHA_ERRADA
"Senha ou usuário inválidos!"

login monica@gmail.com sansao123
"Logado com monica@gmail.com"
```
#### **disconnect**
Desconecta o usuário atual do sistema, resetando as variáveis que armazenam o ID do usuário logado, o servidor e o canal que estavam sendo visualizados. É necessário ter algum usuário logado.

_Exemplo de entrada/saída:_
```console
disconnect
"Desconectando usuário monica@gmail.com"

disconnect
"Não está conectado"
```
#### **create-server**
Cria um novo servidor, caso não exista nenhum com o mesmo nome. Cadastra o usuário logado como o dono do servidor, que inicialmente não possui descrição nem código de convite. É necessário ter algum usuário logado.

_Exemplo de entrada/saída:_
```console
create-server dona-da-rua
"Não está conectado"

login monica@gmail.com sansao123
"Logado com monica@gmail.com"
create-server dona-da-rua
"Servidor criado"

create-server dona-da-rua
"Servidor com esse nome já existe"
```
#### **set-server-desc**
Altera a descrição de um servidor, caso ele exista. É necessário que o usuário logado seja o dono.

_Exemplo de entrada/saída:_
```console
set-server-desc dona-da-rua Onde Mônica é rainha e o resto nadinha
"Descrição do servidor 'dona-da-rua' modificada!"

set-server-desc dona-da-rua2 Onde Mônica é rainha e o resto nadinha
"Servidor 'dona-da-rua2' não encontrado"

login cebolinha@gmail.com senha
"Logado com cebolinha@gmail.com"
set-server-desc dona-da-rua Mônica golducha, baixinha e dentuça
"Você não pode alterar a descrição de um servidor que não foi criado por você"
```
#### **set-server-invite-code**
Insere ou remove o código de convite de um servidor, caso ele exista. É necessário que o usuário logado seja o dono.

_Exemplo de entrada/saída:_
```console
set-server-invite-code dona-da-rua 123
"Código de convite do servidor 'dona-da-rua' modificado!"

set-server-invite-code dona-da-rua
"Código de convite do servidor 'dona-da-rua' removido!"

set-server-invite-code servidor-inexistente 123
"Servidor 'servidor-inexistente' não encontrado"
```
#### **list-servers**
Exibe uma lista com os nomes dos servidores atuais do sistema. É necessário ter algum usuário logado.

_Exemplo de entrada/saída:_
```console
list-servers
"dona-da-rua"
"dono-da-lua"
```
#### **remove-server**
Remove o servidor informado da lista, caso ele exista. É necessário que o usuário logado seja o dono.

_Exemplo de entrada/saída:_
```console
remove-server servidor-inexistente
"Servidor 'servidor-inexistente' não encontrado"

remove-server dona-da-rua
"Servidor 'dona-da-rua' removido"

remove-server dono-da-lua
"Você não é dono(a) do servidor 'dono-da-lua'"
```
#### **enter-server**
Adiciona o ID do usuário na lista de membros do servidor, caso ele exista. Para isso, o servidor precisa ser aberto, ou o usuário deve inserir o código de convite correto, ou ser o dono do servidor. É necessário ter algum usuário logado.

_Exemplo de entrada/saída:_
```console
enter-server receitinhas 123
"Entrou no servidor com sucesso"

login monica@gmail.com sansao123
"Logado com monica@gmail.com"
enter-server receitinhas
"Servidor requer código de convite"

enter-server bairro-do-limoeiro
"Entrou no servidor com sucesso"
```
#### **leave-server**
O usuário logado deixa de visualizar o servidor, ou seja, reseta a propriedade que armazena o nome do servidor visualizado no momento. O ID dele ainda permanece na lista de membros. É necessário ter algum usuário logado e ter algum servidor conectado.

_Exemplo de entrada/saída:_
```console
leave-server receitinhas
"Saindo do servidor 'receitinhas'"

leave-server receitinhas
"Você não está visualizando nenhum servidor"
```
#### **list-participants**
Exibe uma lista com os nomes dos membros do servidor atual. É necessário ter algum usuário logado e ter algum servidor conectado.

_Exemplo de entrada/saída:_
```console
list-participants
"Você não está visualizando nenhum servidor"

list-participants
"Membros de 'bairro-do-limoeiro':"
"Cebolinha"
"Magali"
"Mônica"
```
### Parte 2
Comandos relacionados a gestão de canais e mensagens. Todos exigem que exista um usuário logado e que ele esteja conectado a algum servidor.

#### **create-channel**
Cria um novo canal no servidor atual com o nome e o tipo passados por parâmetro. É possível criar canais de mesmo nome e tipos diferentes.

_Exemplo de entrada/saída:_
```console
create-channel chat texto
"Canal de texto 'chat' criado"

create-channel chat texto
"Canal de texto 'chat' já existe!"

create-channel joguinhos voz
"Canal de voz 'joguinhos' criado"
```
#### **list-channels**
Exibe uma lista com os canais de texto e de voz do servidor atual.

_Exemplo de entrada/saída:_
```console
list-channels
"#canais de texto
chat
clube-do-livro
#canais de voz
joguinhos"
```
#### **enter-channel**
Altera a variável que armazena qual canal está sendo visualizado no momento para o canal cujo nome foi inserido, se ele existir. Se houver mais de um canal com o mesmo nome, entra no primeiro encontrado.

_Exemplo de entrada/saída:_
```console
enter-channel clube-do-livro
"Entrou no canal 'clube-do-livro'"

enter-channel memes
"Canal 'memes' não existe"
```
#### **leave-channel**
O usuário logado deixa de visualizar o canal, ou seja, reseta a propriedade que armazena o nome do canal visualizado no momento, caso exista um.

_Exemplo de entrada/saída:_
```console
leave-channel
"Saindo do canal 'clube-do-livro'"

leave-channel
"Você não está visualizando nenhum canal"
```
#### **send-message**
Adiciona uma nova mensagem ao canal atual (é necessário estar conectado a um). Se for um canal de texto, adiciona ao final da lista. Se for um canal de voz, sobrescreve a última mensagem enviada. O objeto da mensagem guarda o ID de quem enviou, o conteúdo e a data e hora de envio.

_Exemplo de entrada/saída:_
```console
enter-channel chat
send-message Oi turminha, vou entrar no canal de voz
"Mensagem enviada"

enter-channel joguinhos
send-message Estão me ouvindo?
"Mensagem enviada"
```
#### **list-messages**
Exibe todas as mensagens do canal atual(é necessário estar conectado a um), contendo o nome de quem enviou, a data/hora de envio e o conteúdo.

_Exemplo de entrada/saída:_
```console
list-messages
"Mônica<17:08 - 11/04/2021>: Oi turminha, vou entrar no canal de voz
Cebolinha<17:10 - 11/04/2021>: Vamos de Mineclaft?
Magali<17:10 - 11/04/2021>: Vou fazer um lanchinho, volto já"

list-messages
"Sem mensagens para exibir"
```
### Parte 3
Nesta etapa não foram adicionados comandos novos, mas um mecanismo que salva todos os dados do sistema (usuários, servidores, canais e mensagens) em disco e que carrega esses dados para que o sistema retome o estado desde a última execução.
#### **Persistência dos dados em disco**
O método **save()** é executado automaticamente após comandos que alteram algum dado do sistema (criação de usuários, mudança na descrição de um servidor, envio de mensagens e etc). Este método executa **saveUsers()** e **saveServers()**, que percorrem as listas de usuários e servidores do sistema e salvam suas informações nos arquivos **users.txt** e **servers.txt**, respectivamente.

O método **saveUsers()** escreve no arquivo com o seguinte padrão:
* Primeira linha contém o total de usuários
* Em seguida, para cada usuário, existem 4 linhas, uma para cada atributo na seguinte ordem: ID, nome, email, senha

_Exemplo de arquivo "users.txt":_
```console
3
1
Mônica
monica@gmail.com
sansao123
2
Cebolinha
cebolinha@gmail.com
senha
3
Magali
magali@gmail.com
mingau123
```
O método **saveServers()** escreve no arquivo com o seguinte padrão:
* Primeira linha contém o total de servidores
* Em seguida, para cada servidor, temos:
  * Uma linha com o ID do usuário dono do servidor
  * Uma linha com o nome do servidor
  * Uma linha com a descrição do servidor
  * Uma linha com o código de convite do servidor (se for aberto deve ser uma linha vazia)
  * Uma linha com o número de usuários participantes do servidor
  * Para cada usuário, uma linha com o ID
  * Uma linha com o número de canais do servidor
  * Para cada canal:
    * Uma linha com o nome do canal
    * Uma linha com o tipo do canal: 'TEXTO' ou 'VOZ'
    * Uma linha com o número de mensagens do canal
    * Para cada mensagem do canal:
      * Uma linha com o ID do usuário que a enviou
      * Uma linha com a data/hora de envio
      * Uma linha com o conteúdo da mensagem

_Exemplo de situação:_

Ao rodar o programa com os comandos do script2.txt, teremos 2 servidores:
* Servidor bairro-do-limoeiro com:
  * Descrição "Onde as aventuras acontecem"
  * 2 participantes: Monica (ID 1) e Magali (ID 2)
  * 1 canal de texto "geral" e 1 de voz "joguinhos"
    * Canal "geral" com duas mensagens, uma de Monica com o conteúdo "Oi turminha, vou entrar no canal de voz" e uma de Magali com o conteúdo "Oi amiga"
    * Canal "joguinhos" com a mensagem de Monica "Estão me ouvindo?"
* Servidor dono-da-lua com:
  * Descrição "Onde nascem os planos infaliveis"
  * 1 participante: Cebolinha (ID 3)
  * 1 canal de texto "ideias" com duas mensagens "almadilha de colda" e "pega o coelho encaldido e sai colendo", ambas do Cebolinha


_Exemplo de arquivo "servers.txt" para a situação acima:_
```console
2
1
bairro-do-limoeiro
Onde as aventuras acontecem

2
1
2
2
geral
TEXTO
2
1
15:00 - 21/04/2021
Oi turminha, vou entrar no canal de voz
2
15:05 - 21/04/2021
Oi amiga
joguinhos
VOZ
1
1
15:05 - 21/04/2021
Estão me ouvindo?
3
dono-da-lua
Onde nascem os planos infaliveis

1
3
1
ideias
TEXTO
2
3
15:09 - 21/04/2021
almadilha de colda
3
16:00 - 21/04/2021
pega o coelho encaldido e sai colendo
```
#### **Restauração dos dados do disco**
O método **load()** é executado automaticamente na inicialização do sistema para retormar o estado da aplicação e antes de cada um dos comandos, para recuperar as informações que podem ter sido alteradas por outro usuário em execução simultânea. Se os arquivos **users.txt** e **servers.txt** existirem e não estiverem vazios, este método executa **loadUsers()** e **loadServers()** que percorrem todas as linhas desses arquivos e preenchem os vetores do sistema com as informações de usuários e servidores (com seus participantes, canais e mensagens).

Para detalhes da implementação de cada um desses métodos, verifique os comentários no código do arquivo system.cpp.
## Licença e Autora
Este projeto está sob a licença MIT. Veja o arquivo [LICENSE](https://github.com/lorenatoscano/concordo/blob/main/LICENSE) para mais detalhes.

Feito por [Luiza Lorena Toscano de Medeiros](https://github.com/lorenatoscano) com base no template base do professor [Isaac Franco Fernandes](https://github.com/isaacfranco).
