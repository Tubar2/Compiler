cmake_minimum_required(VERSION 3.17)
project(Trab_SB_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Trab_SB_1 montador.cpp database/types.hpp aux_functions/aux.cpp aux_functions/aux.hpp database/tables.hpp)