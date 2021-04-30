//
// Created by Ricardo Santos on 09/03/21.
//


#ifndef TRAB_SB_1_MONTADOR_AUX_HPP
#define TRAB_SB_1_MONTADOR_AUX_HPP

#include "first_pass/first_pass_aux.hpp"
#include "second_pass/second_pass_aux.hpp"


// Lê o arquivo .asm e retorna um Modulo
// O módulo é um objeto com tabelas
// Cada instrução é um struct {Cooment, Label, Operation, Operands, Inst_line}
table::Module firstPass(const std::string& filename);

// Aplica o algoritmo de primeira passagem e retorna um vetor instruções pre-.obj
table::Object_Code secondPass(table::Module & module);

// Substituir símbolos e rótulos não criados pelo seu endereço
void removePendency(const std::vector<std::vector<std::string> *>& obj_file);

// Vê se o arquivo final teve error e os lista
bool checkForErrors();

// Cria o arquivo .obj corretamente formatado
void createObj(const std::vector<std::vector<std::string> *>& obj_file, const std::string& name);
#endif //TRAB_SB_1_MONTADOR_AUX_HPP
