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
        if (operand == ".text" || operand == ".data") {
            table::header_insertion_flag = false;
            if (operand == ".text") {
                table::text_insertion_flag = true;
            }
        }
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

void fPass_defineLabel(table::Instruction &instruction, table::Module &module) {
    bool inMap = module.symbolsTable.find(instruction.label) != module.symbolsTable.end();
    if (!inMap) {
        // Caso begin
        if (!instruction.operation.empty()){
            if (instruction.operation == "begin") {
                module.insertLabelSymbols(instruction.label, 0, false);
                module.header.name = instruction.label;
            } else if (instruction.operation == "extern"){
                module.insertLabelSymbols(instruction.label, 0, true);
            } else {
                // TODO: Erro, diretiva inválida
            }
        }
        // TODO; Erro, num operandos inválido
    }
    else {
        //TODO: Erro, label redefinido
    }
}

void fPass_defineOperation(table::Instruction &instruction, table::Module &module) {
    bool isInstruction = table::inst_set.find(instruction.operation) != table::inst_set.end();
    if (isInstruction){
        if (instruction.operation == "public"){
            if (instruction.operands.size() == 1){
                module.defineLabel(instruction.operands[0], 0);
                bool inSymbolTable = module.symbolsTable.find(instruction.operands[0]) != module.symbolsTable.end();
                if (inSymbolTable && module.labelIsExtern(instruction.operands[0])){
                    // TODO: Erro símbolo externo redefinido como publico
                }
            } else {
                // TODO: Erro quadntidade de operandos
            }
        }
    } else {
        // TODO: Erro Operação não definida
    }
}

void defineBegindExternPublic(table::Instruction &instruction, table::Module &module){
    // Caso begin ou extern
    if (!instruction.label.empty()){
        fPass_defineLabel(instruction, module);
    }
    // Caso public
    else if (!instruction.operation.empty()){
        fPass_defineOperation(instruction, module);
    }
}

void defineVariables(table::Instruction &instruction, table::Module &module, int & posCounter){
    if (!instruction.label.empty()){
        if (!instruction.operation.empty()){
            auto directive = table::directive_set.find(instruction.operation);
            bool isDirective = directive != table::directive_set.end();
            if (isDirective){
                bool isInSymbols = module.symbolsTable.find(instruction.label) != module.symbolsTable.end();
                if (!isInSymbols){
                    module.insertLabelSymbols(instruction.label, posCounter, false);
                } else {
                    // TODO: Erro

                }
                posCounter += directive->second.size;
            }
        }
    }
}

void defineLabels(table::Instruction &instruction, table::Module &module, int & posCounter){
    if (!instruction.label.empty()){
        bool isInSymbols = module.symbolsTable.find(instruction.label) != module.symbolsTable.end();
        if (!isInSymbols){
            module.insertLabelSymbols(instruction.label, posCounter, false);
        } else {
            // TODO: Erro
        }
    }
    if (!instruction.operation.empty()){
        auto operation = table::inst_set.find(instruction.operation);
        bool isOperation = operation != table::inst_set.end();
        if (isOperation){
            posCounter += operation->second.size;
        }
    }
}

void correctDataAddr(table::Instructions_Set & data, table::Module & module, int posCounter_text){
    for (auto & instruction : data){
        if (!instruction.label.empty()){
            module.symbolsTable[instruction.label].addr += posCounter_text;
        }
    }
}