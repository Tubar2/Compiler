//
// Created by Ricardo Santos on 30/04/21.
//

#include "first_pass_aux.hpp"


table::Label checkLabel(table::Label & word, table::Module & module, int lineCounter){
    assert_firstLetterNotNumber(word, module, lineCounter);
    word.pop_back(); // Remove ':'
    assert_wordLengthLessThan50(word, module, lineCounter);
    return word;
}

table::Operands createOperands(const std::string& operands_string){
    // TODO: Alterar a função para popular as tabelas de definição e uso
    table::Operands operands {};
    std::istringstream iss {operands_string};
    std::string operand {};
    while (std::getline(iss, operand, ',')){
        if (operand == "text") {table::text_insertion_flag = true;}
        operands.push_back(operand);
    }
    return operands;
}

void correctLabel(table::Label & s){
    const std::string WHITESPACE = " \n\r\t\f\v";
    size_t start = s.find_first_not_of(WHITESPACE);
    s = (start == std::string::npos) ? "" : s.substr(start);

    auto foundLSpace = s.find(" :");
    auto foundFSpace = s.find(' ');
    if (foundLSpace != std::string::npos){
        auto erase = foundLSpace - foundFSpace + 1;
        s.erase(foundFSpace, erase);
    }
}

void fPass_defineLabel(table::Instruction &instruction, table::Module &module, int posCounter) {
    bool inMap = module.symbolsTable.find(instruction.label) != module.symbolsTable.end();
    if (!inMap) {
        module.symbolsTable[instruction.label] = {posCounter, false};
    } else {
        if (!module.symbolsTable[instruction.label].isExtern){
            module.symbolsTable[instruction.label].addr = posCounter;
        }
        //TODO: Erro, label redefinido
    }
}

void fPass_defineOperation(table::Instruction &instruction, table::Module &module, int &counter) {
    bool isDirective = table::directive_set.find(instruction.operation) != table::directive_set.end();
    if (isDirective){
        // TODO: Verificar para quando uma label previamente definida como publica é redefinida para externa
        if (instruction.operation == "extern"){
            if (!instruction.label.empty()){
                module.symbolsTable[instruction.label].isExtern = true;
            } else{
                // TODO: Erro variável externa não definida
            }
        }
        if (instruction.operation == "begin"){
            if (!instruction.label.empty()){
                module.header.name = instruction.label;
            } else{
                // TODO: Erro variável "begin" não definida
            }
        }
        counter += table::directive_set[instruction.operation].size;
    } else{
        bool isInstruction = table::inst_set.find(instruction.operation) != table::inst_set.end();
        if (isInstruction){
            if (instruction.operation == "public"){
                if (instruction.operands.size() == 1){
                    bool inSymbolTable = module.symbolsTable.find(instruction.operands[0]) != module.symbolsTable.end();
                    if (!inSymbolTable){
                        module.symbolsTable.insert({instruction.operands[0], {counter, false}});
                    } else if (module.labelIsExtern(instruction.operation)){
                        // TODO: Erro, redefinição de label externa
                    }
                } else {
                    // TODO: Erro quadntidade de operandos
                }
            }
            counter = table::inst_set[instruction.operation].size;
        } else {
            // TODO: Operação não definida
        }
    }

}