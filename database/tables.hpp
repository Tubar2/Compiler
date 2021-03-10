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

    // Tabela de diretivas
    static std::map<Directive_Name, int> directive_set{
            {"space", 0},
            {"const", 1},
    };

    // Tabela de instruções
    static std::map<Opcode_Name, Opcode_Struct> inst_set{
            {"add",    {2, "01"}},
            {"sub",    {2, "02"}},
            {"mul",    {2, "03"}},
            {"div",    {2, "04"}},
            {"jmp",    {2, "05"}},
            {"jmpn",   {2, "06"}},
            {"jmpp",   {2, "07"}},
            {"jmpz",   {2, "08"}},
            {"copy",   {3, "09"}},
            {"load",   {2, "10"}},
            {"store",  {2, "11"}},
            {"input",  {2, "12"}},
            {"output", {2, "13"}},
            {"stop",   {1, "14"}},
    };

    // Tabela de simbolos
    static std::map<Label, addr> symbols{};

    // Lista de pendencias
    static std::vector<Pendency> pendencies{};

    // Lista de erros
    static std::vector<Error> errors{};
}

#endif //TRAB_SB_1_TABLES_HPP
