//
// Created by Ricardo Santos on 30/04/21.
//

#ifndef TRAB_SB_1_ERROR_HANDLING_HPP
#define TRAB_SB_1_ERROR_HANDLING_HPP

#include "../database/types.hpp"
#include "../database/tables.hpp"

// Verifica que o token não começa com dígito
void assert_isNotDigit(const std::string & token, table::Module & module, const int line);

// Verifica que foi fornecido o número correto de operandos, dada a operação
void assert_correctNumOperands(const table::Instruction & instruction, table::Module & module);

// Verifica que o operando para a diretiva "const" é um número (negativo ou positivo)
bool assert_constReceivesDecimal(const table::Instruction & instruction, table::Module & module);

// Verifica que a operação recebe o número correto de operandos
void assert_operationReceivesNumOperands(int size, const table::Instruction & instruction, table::Module & module);

// Verifica que o primeiro caractér é um digito
void assert_firstLetterNotNumber(const std::string & word, table::Module & module, int lineCounter);

// Verifica se o label possui menos que 50 caractéres
void assert_wordLengthLessThan50(const std::string & word, table::Module & module, int lineCounter);

// Verifica que a operação não é uma instruçao ou diretiva válida
void assert_isNotDirectiveOrOperation(const table::Instruction & instruction, table::Module & module);

#endif //TRAB_SB_1_ERROR_HANDLING_HPP
