//
// Created by Ricardo Santos on 09/03/21.
//

#ifndef TRAB_SB_1_TYPES_HPP
#define TRAB_SB_1_TYPES_HPP

#include <vector>
#include <map>
#include <string>
#include <array>

namespace table {
    //////////////////////////////////
    /* TIPOS E ESTRUTURA AUXILIARES */
    //////////////////////////////////

    // Aliases para tipos string
    typedef std::string Opcode_Name, Label, Directive_Name, Comment, Operation, Prog_Name;
    // Aliases para tipos int
    typedef int Address, Inst_Line, Opcode_Num;

    // Uma operação pode ter de 0-2 operandos
    typedef std::vector<std::string> Operands;

    // Programa como código objeto
    // É um vector<int> apenas com os números após 'end xx.' no exemplo abaixo:
    // end 00. 12  0
    // end 02. 10  11
    // end 04. 14
    // end 05. 5
    // => [12, 0, 10, 11, ...]
    typedef std::vector<int> Object_Code;

    // Estrutura de uma linha de instrução
    typedef struct Instruction {
        Comment comment;
        Label label;
        Operation operation;
        Operands operands;
        Inst_Line line;
    } Instruction;

    // Estrutura com número de Operands e tamanho
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
//    typedef struct Pendency{
//        int line;
//        Instruction_Address pendency;
//    } Pendency;

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

        ////////////////////////////////
        /* TABELAS E LISTAS DO MÓDULO */
        ////////////////////////////////

        // Tabela de Definições
        std::map<Label, Address> definitionsTable {};

        // Tabela de Uso
        std::map<Label, Address> usesTable {};

        // Tabela de simbolos
        // map<Label, Value>, onde
        // Label = String
        // Value = {Int, bool}
        std::map<Label, Value> symbolsTable{};

        // Lista de erros
        std::vector<Error> errorsList{};

        // Retorna true caso uma label foi definida como externa na tabela de símbolos
    public:
        bool labelIsExtern(Label label){
            return symbolsTable[label].isExtern;
        }
        void pushError(Error err){
            errorsList.push_back(err);
        }
        void defineLabel(Label label, Address addr){
            definitionsTable.insert({label, addr});
        }
        void insertLabelUseCase(Label label, Address addr){
            usesTable.insert({label, addr});
        }
        int getLabelAddr(Label label){
            return symbolsTable[label].addr;
        }

    } Module;

    // Um Module_Set corresponde a um conjunto de módulos
    typedef std::vector<Module> Module_Set;
} // namespace table

#endif //TRAB_SB_1_TYPES_HPP
