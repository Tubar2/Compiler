aux = $(wildcard ./aux/$@/$@_aux.cpp)
#database = $(wildcard ./database/*.hpp)
compile_cpp = g++ -Wall -std=c++11 -c

all: montador simulador

montador: montador.o montador_aux.o
	g++ montador.o montador_aux.o -o montador

montador.o: montador.cpp
	$(compile_cpp) montador.cpp

montador_aux.o: ./aux/montador/montador_aux.cpp
	$(compile_cpp) ./aux/montador/montador_aux.cpp

simulador: simulador.o simulador_aux.o
	g++ simulador.o simulador_aux.o -o simulador

simulador.o: simulador.cpp
	$(compile_cpp) simulador.cpp

simulador_aux.o:
	$(compile_cpp) ./aux/simulador/simulador_aux.cpp

clean:
	rm *.o