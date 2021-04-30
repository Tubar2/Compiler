//
// Created by Ricardo Santos on 30/04/21.
//
#include "../error_handling.hpp"


void assert_firstLetterNotNumber(const std::string & word, table::Module & module, int lineCounter){
    if(isdigit(word[0])){
        module.pushError({
            "Erro na nomenclatura do label '" + word + "'",
            "Léxico",
            lineCounter
        });
    }
}

void assert_wordLengthLessThan50(const std::string & word, table::Module & module, int lineCounter){
    if (word.length() > 50){
        module.pushError({
            "Nome do label excede limite de caractéres",
            "Léxico",
            lineCounter
        });
    }
}