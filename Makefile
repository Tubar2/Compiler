compile_cpp = g++ -Wall -std=c++11 -c
aux = $@.o $@_aux.o -o $@

all: montador simulador


montador: montador.o montador_aux.o
	g++ $(aux)

simulador: simulador.o simulador_aux.o
	g++ $(aux)


montador.o: montador.cpp
	$(compile_cpp) montador.cpp

montador_aux.o: ./aux/montador/montador_aux.cpp ./aux/montador/montador_aux.hpp first_pass_aux.o second_pass_aux.o
	$(compile_cpp) ./aux/montador/montador_aux.cpp

first_pass_aux.o: ./aux/montador/first_pass/first_pass_aux.cpp ./aux/montador/first_pass/first_pass_aux.hpp error_handling.o

second_pass_aux.o: ./aux/montador/second_pass/second_pass_aux.cpp ./aux/montador/second_pass/second_pass_aux.hpp error_handling.o

error_handling.o: ./error/error_handling.hpp ./database/tables.hpp ./database/tables.hpp

lexic.o: ./error/Lexic/lexic.cpp

semantic.o: ./error/Semantic/semantic.cpp

lexic.o: ./error/Sintatic/sintatic.cpp

simulador.o: simulador.cpp
	$(compile_cpp) simulador.cpp

simulador_aux.o: ./aux/simulador/simulador_aux.cpp ./database/tables.hpp ./database/tables.hpp
	$(compile_cpp) ./aux/simulador/simulador_aux.cpp

clean:
	rm -vf *.o montador simulador *.obj *.out