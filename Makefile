.DEFAULT_GOAL := all

all: concordo

# Compila tudo e cria o executável "concordo"
concordo: objects
	g++ *.o -Iinclude -std=c++11 -Wall -o concordo

main.o: src/main.cpp system.o executor.o user.o
	g++ src/main.cpp -Iinclude -c

system.o: src/system.cpp user.o
	g++ src/system.cpp -Iinclude -c

executor.o: src/executor.cpp system.o
	g++ src/executor.cpp -Iinclude -c

user.o: src/user.cpp
	g++ src/user.cpp -Iinclude -c

objects: main.o system.o executor.o user.o

clean:
	rm *.o concordo

run:
	./concordo
