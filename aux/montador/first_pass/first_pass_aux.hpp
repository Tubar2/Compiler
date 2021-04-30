//
// Created by Ricardo Santos on 30/04/21.
//

#ifndef TRAB_SB_1_FIRST_PASS_AUX_HPP
#define TRAB_SB_1_FIRST_PASS_AUX_HPP

#include <sstream>
#include <fstream>
#include <iostream>

#include "../../../error/error_handling.hpp"


/*------------------------------------------
| Funções auxilares do algoritmo first pass |
-------------------------------------------*/

// Inserir a label na Tabela de Simbolos do módulo
// Se a label ja foi definida, lançará erro
void fPass_defineLabel(table::Instruction &instruction, table::Module &module, int posCounter);

// Inserir ou redefinir alguns símbolos criados pelas diretivas
// extern, public ou begin
void fPass_defineOperation(table::Instruction &instruction, table::Module &module, int &counter);

/*------------------------------------
| Funções para formatar as instruções |
-------------------------------------*/

// Checar se o label foi corretamente criado
table::Label checkLabel(table::Label & word, table::Module & module, int lineCounter);

// Separa uma string com operandos por ','
// "op1,op2" -> ["op1", "op2"]
table::Operands createOperands(const std::string& operands_string);

// Remove espaço em branco para evitar erros como
// ["  Label:" ou "   Label:   " ou "  Label  : "] -> "Label:  "
void correctLabel(table::Label & s);

#endif //TRAB_SB_1_FIRST_PASS_AUX_HPP
