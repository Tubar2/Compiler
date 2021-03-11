//
// Created by Ricardo Santos on 09/03/21.
//


#ifndef TRAB_SB_1_MONTADOR_AUX_HPP
#define TRAB_SB_1_MONTADOR_AUX_HPP
#include <fstream>
#include <iostream>
#include <sstream>
#include "../../database/types.hpp"

// Lê o arquivo .asm e ppopula o vetor de Instrução
void readFile(const std::string& filename, std::vector<table::Instruction> & instructions);

// Aplica o algoritmo de primeira passagem e retorna um vetor instruções pre-.obj
std::vector<std::vector<std::string> *> secondPass(const std::vector<table::Instruction>& instructions);

// Substituir símbolos e rótulos não criados pelo seu endereço
void removePendency(const std::vector<std::vector<std::string> *>& obj_file);

// Vê se o arquivo final teve error e os lista
bool checkForErrors();

// Cria o arquivo .obj corretamente formatado
void createObj(const std::vector<std::vector<std::string> *>& obj_file, const std::string& name);
#endif //TRAB_SB_1_MONTADOR_AUX_HPP
