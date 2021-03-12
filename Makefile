aux = $(wildcard ./aux/$@/$@_aux.cpp)
compile_cpp = g++ -Wall -std=c++11 -c
aux = $@.o $@_aux.o -o $@

all: montador simulador


montador: montador.o montador_aux.o
	g++ $(aux)

simulador: simulador.o simulador_aux.o
	g++ $(aux)


montador.o: montador.cpp
	$(compile_cpp) montador.cpp

montador_aux.o: ./aux/montador/montador_aux.cpp ./database/tables.hpp ./database/tables.hpp
	$(compile_cpp) ./aux/montador/montador_aux.cpp

simulador.o: simulador.cpp
	$(compile_cpp) simulador.cpp

simulador_aux.o: ./aux/montador/montador_aux.cpp ./database/tables.hpp ./database/tables.hpp
	$(compile_cpp) ./aux/simulador/simulador_aux.cpp

clean:
	rm -v *.o montador simulador montador.obj