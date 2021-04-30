//
// Created by Ricardo Santos on 09/03/21.
//

#ifndef TRAB_SB_1_TYPES_HPP
#define TRAB_SB_1_TYPES_HPP

#include <vector>
#include <map>
#include <string>

namespace table {
    //////////////////////////////////
    /* TIPOS E ESTRUTURA AUXILIARES */
    //////////////////////////////////

    // Aliases para tipos string
    typedef std::string Opcode_Name, Opcode_Num, Label, Directive_Name, Comment, Operation;
    // Aliases para tipos int
    typedef int Address, Inst_Line;

    // Estrutura auxilar para identificar se o símbolo é externo
    typedef struct Value {
        Address addr;
        bool isExtern;
    } Value;

    // Uma operação pode ter de 0-2 operandos
    typedef std::vector<std::string> Operands;

    // Estrutura de uma linha de instrução
    typedef struct Instruction {
        Comment comment;
        Label label;
        Operation operation;
        Operands operands;
        Inst_Line line;
    } Instruction;

    // Estrtura do opcode -> Será usado na tabela de hash (nome do opcode -> estrutura do opcode)
    typedef struct Opcode_Struct{
        int size;               // Quantidade de operandos
        Opcode_Num opcode_num;  // Instrução em decimal
    } Opcode_Struct;

    // Estrutura de um erro <nome, tipo, linha de ocorrência>
    typedef struct Error {
        std::string error;
        std::string error_type;
        int line;
        // Overloading o opeardo '<' para poder organizar a lista de erros por linha
        bool operator< (const Error &err) const {return line < err.line ;}
    } Error;

    // Estrutura de uma pendência <linha de ocorrência, endereço da linha>
    typedef struct Pendency{
        int line;
        std::vector<std::string> * pendency;
    } Pendency;

    // Um Module corresponde a um vetor de instruções
    typedef std::vector<Instruction> Module;

    // Um Module_Set corresponde a um conjunto de módulos
    typedef std::vector<Module> Module_Set;
} // namespace table

#endif //TRAB_SB_1_TYPES_HPP
