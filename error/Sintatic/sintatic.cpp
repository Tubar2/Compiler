//
// Created by Ricardo Santos on 30/04/21.
//

#include "../error_handling.hpp"

// Verifica se uma string é um dígito
bool is_decimal(const std::string & num);

void assert_isNotDigit(const std::string & token, table::Module & module, int line){
    if ( std::isdigit(token[0])){
        module.pushError({
            "Tipo de operando '" + token + "' inválido",
            "Sintático",
            line
        });
    }
}

void assert_correctNumOperands(const table::Instruction & instruction, table::Module & module){
    if (instruction.operands.size() != table::inst_set[instruction.operation].size-1){
        module.errorsList.push_back({
                "Instrução '" + instruction.operation + "' com número ilegal de operandos. Esperava: " +
                std::to_string(table::inst_set[instruction.operation].size-1) +
                ". Recebeu: " + std::to_string(instruction.operands.size()),
                "Sintático",
                instruction.line
        });
    }
}

bool is_decimal(const std::string & num){
    // TODO: Verificar aqui
    std::string::const_iterator it = num.begin();
    if (num[0] == '-'){
        num.begin() + 1;
    }
    while (it != num.end() && (std::isdigit(*it))) ++it;
    return !num.empty() && it == num.end();
}

bool assert_constReceivesDecimal(const table::Instruction & instruction, table::Module & module){
    if (!is_decimal(instruction.operands[0])) {
        module.pushError({
            "Operando inválida na diretiva 'const'. Esperava decimal. Recebeu: '" + instruction.operands[0] + "'",
            "Sintático",
            instruction.line
        });
        return false;
    }
    return true;
}

void assert_operationReceivesNumOperands(const table::Instruction & instruction, table::Module & module){
    int size = table::directive_set[instruction.operation].operands;
    if (instruction.operands.size() != size){
        module.pushError({
            "Diretiva '" + instruction.operation + "' com número ilegal de operandos. Esperava: " +
            std::to_string(size) + ". Recebeu: " + std::to_string(instruction.operands.size()),
            "Sintático",
            instruction.line
         });
    }
}

void assert_modulesHaveEnd(table::Module_Set & modules){
    if (modules.size() > 1){
        for (auto & module : modules){
            if (module.header.name.empty()){
                module.pushError({
                    "Módulo: " + module.filename +" não possui diretiva \"begin\"",
                    "Sintático",
                    0
                });
            }
            if (!module.has_end) {
                module.pushError({
                    "Módulo: " + module.filename + " não possui diretiva \"end\"",
                    "Sintático",
                    static_cast<int>(module.instructions.size() + 1)
                });
            }
        }
    }
}