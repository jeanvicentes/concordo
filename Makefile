.DEFAULT_GOAL := all

all: concordo

# Compila tudo e cria o executável "musify"
concordo: objects
	g++ *.o -Iinclude -std=c++11 -Wall -o concordo

main.o: src/main.cpp sistema.o executor.o usuario.o
	g++ src/main.cpp -Iinclude -c

sistema.o: src/sistema.cpp usuario.o
	g++ src/sistema.cpp -Iinclude -c

executor.o: src/executor.cpp sistema.o
	g++ src/executor.cpp -Iinclude -c

usuario.o: src/usuario.cpp
	g++ src/usuario.cpp -Iinclude -c

objects: main.o sistema.o executor.o usuario.o

clean:
	rm *.o concordo

run:
	./concordo
