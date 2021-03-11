cmake_minimum_required(VERSION 3.17)
project(Trab_SB_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Trab_SB_1 montador.cpp database/types.hpp aux/montador/montador_aux.cpp aux/montador/montador_aux.hpp database/tables.hpp)
add_executable(simulador simulador.cpp database/types.hpp aux/montador/montador_aux.cpp aux/montador/montador_aux.hpp database/tables.hpp aux/simulador/simulador_aux.cpp aux/simulador/simulador_aux.hpp)