//
// Created by Ricardo Santos on 30/04/21.
//

#ifndef TRAB_SB_1_SECOND_PASS_AUX_HPP
#define TRAB_SB_1_SECOND_PASS_AUX_HPP


#include "../../../error/error_handling.hpp"

/*-------------------------------------------
| Funções auxilares do algoritmo second pass |
--------------------------------------------*/

// Ao executar uma diretiva (ja válidada), retorna a quantidade de bytes que ocupa
// Checa caso o número de operandos foi devidamente fornecido
int execDirective(const table::Instruction & instruction, table::Object_Code & obj_file, table::Assembly_Module & module);

//
int execInstruction(const table::Instruction & instruction, table::Object_Code & obj_file, table::Assembly_Module & module);

/*------------------------------------
| Funções para formatar as instruções |
-------------------------------------*/


#endif //TRAB_SB_1_SECOND_PASS_AUX_HPP
