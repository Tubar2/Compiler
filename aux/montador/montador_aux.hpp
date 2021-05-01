//
// Created by Ricardo Santos on 09/03/21.
//


#ifndef TRAB_SB_1_MONTADOR_AUX_HPP
#define TRAB_SB_1_MONTADOR_AUX_HPP

#include "first_pass/first_pass_aux.hpp"
#include "second_pass/second_pass_aux.hpp"


// Lê o arquivo .asm e retorna um Modulo
// O módulo é um objeto com tabelas
// Após o algoritmo firstPass as tabelas de símbolos e definições estarão preenchidas
// Cada instrução é um struct {Cooment, Label, Operation, Operands, Inst_line}
table::Module firstPass(const std::string& filename);

void correctDefinitionsTable(table::Module & module);

// Aplica o algoritmo de primeira passagem e retorna um vetor instruções pre-.obj
table::Object_Code secondPass(table::Module & module);

// Vê se o arquivo final teve error e os lista
bool checkForErrors(table::Module & module);

// Cria o arquivo .obj corretamente formatado
void createObj(const table::Module & module, const std::string& name);
#endif //TRAB_SB_1_MONTADOR_AUX_HPP
