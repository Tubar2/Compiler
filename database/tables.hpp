//
// Created by Ricardo Santos on 09/03/21.
//

#ifndef TRAB_SB_1_TABLES_HPP
#define TRAB_SB_1_TABLES_HPP
#include "types.hpp"

namespace table {
    /////////////////////////////////
    /* TABELAS E LISTAS AUXILIARES */
    /////////////////////////////////

    // Flag de inserção no início ou fim da lista de instruções
    static bool text_insertion_flag {false};

    // Tabela de diretivas
    static std::map<Directive_Name, int> directive_set{
            {"space", 0},
            {"const", 1},
    };

    // Tabela de instruções
    static std::map<Opcode_Name, Opcode_Struct> inst_set{
            {"add",    {2, "1"}},
            {"sub",    {2, "2"}},
            {"mul",    {2, "3"}},
            {"div",    {2, "4"}},
            {"jmp",    {2, "5"}},
            {"jmpn",   {2, "6"}},
            {"jmpp",   {2, "7"}},
            {"jmpz",   {2, "8"}},
            {"copy",   {3, "9"}},
            {"load",   {2, "10"}},
            {"store",  {2, "11"}},
            {"input",  {2, "12"}},
            {"output", {2, "13"}},
            {"stop",   {1, "14"}},
    };

    static std::map<int, int> inst_size{
            {1, 2},
            {2, 2},
            {3, 2},
            {4, 2},
            {5, 2},
            {6, 2},
            {7, 2},
            {8, 2},
            {9, 3},
            {10, 2},
            {11, 2},
            {12, 2},
            {13, 2},
            {14, 1},
    };

    // Tabela de simbolos
    static std::map<Label, addr> symbols{};

    // Lista de pendencias
    static std::vector<Pendency> pendencies{};

    // Lista de erros
    static std::vector<Error> errors{};
}

#endif //TRAB_SB_1_TABLES_HPP
