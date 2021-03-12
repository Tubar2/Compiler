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

    // Aliases para tpos string
    typedef std::string Opcode_Name, Opcode_Num, Label, Directive_Name, Comment, Operation;
    typedef int addr, Inst_line;

    typedef std::vector<std::string> Operands;

    // Estrutura de uma instrução
    typedef struct Instruction {
        Comment comment;
        Label label;
        Operation operation;
        Operands operands;
        Inst_line line;
    } Instruction;

    // Estrtura do opcode
    typedef struct {
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
    typedef struct {
        int line;
        std::vector<std::string> * pendency;
    } Pendency;
} // namespace table

#endif //TRAB_SB_1_TYPES_HPP
