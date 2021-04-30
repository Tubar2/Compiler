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
    typedef std::string Opcode_Name, Opcode_Num, Label, Directive_Name, Comment, Operation, Prog_Name;
    // Aliases para tipos int
    typedef int Address, Inst_Line;

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

    typedef struct Directive_Properties {
        int operands;
        int size;
    } Directive_Properties;

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

    typedef struct Header {
        Prog_Name name;
    } Header;

    typedef std::vector<Instruction> Instructions_Set;

    // Estrutura auxilar para identificar se o símbolo é externo
    typedef struct Value {
        Address addr;
        bool isExtern;
    } Value;

    // Um Module corresponde a um header + vetor de instruções
    typedef struct Module {
        Header header;
        Instructions_Set instructions;

        /////////////////////////////////
        /* TABELAS E LISTAS AUXILIARES */
        /////////////////////////////////

        // Tabela de Definições
        std::map<Label, Address> definitionsTable {};
        // Tabela de Uso
        std::map<Label, Address> usesTable {};
        // Tabela de simbolos
        std::map<Label, Value> symbolsTable{};
    } Module;

    // Um Module_Set corresponde a um conjunto de módulos
    typedef std::vector<Module> Module_Set;
} // namespace table

#endif //TRAB_SB_1_TYPES_HPP
