.DEFAULT_GOAL := all

all: concordo

# Compila tudo e cria o executável "concordo"
concordo: objects
	g++ *.o -Iinclude -std=c++14 -Wall -o concordo

main.o: src/main.cpp system.o executor.o
	g++ src/main.cpp -Iinclude -c

system.o: src/system.cpp user.o server.o textChannel.o voiceChannel.o
	g++ src/system.cpp -Iinclude -c

executor.o: src/executor.cpp system.o
	g++ src/executor.cpp -Iinclude -c

textChannel.o: src/textChannel.cpp message.o
	g++ src/textChannel.cpp -Iinclude -c

voiceChannel.o: src/voiceChannel.cpp message.o
	g++ src/voiceChannel.cpp -Iinclude -c

user.o: src/user.cpp
	g++ src/user.cpp -Iinclude -c

server.o: src/server.cpp
	g++ src/server.cpp -Iinclude -c

message.o: src/message.cpp
	g++ src/message.cpp -Iinclude -c



objects: main.o system.o executor.o user.o server.o

clean:
	rm *.o concordo

run:
	./concordo
