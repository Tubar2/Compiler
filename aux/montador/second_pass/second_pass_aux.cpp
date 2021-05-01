//
// Created by Ricardo Santos on 30/04/21.
//

#include "second_pass_aux.hpp"


int execDirective(const table::Instruction & instruction, table::Object_Code & obj_file, table::Module & module){
    assert_operationReceivesNumOperands(instruction, module);
    if (instruction.operation == "space"){
        module.header.bit_map += "0";
        obj_file.push_back(0);
        return 1;
    }
    if (instruction.operation == "const"){
        // Checar por 0 operandos ou um número não decimal
        if (instruction.operands.empty()){return 0;}
        if ( !assert_constReceivesDecimal(instruction, module) ) {
            return 0;
        }
        module.header.bit_map += "0";
        obj_file.push_back(std::stoi(instruction.operands[0]));
        return 1;
    }
    return 0;
}

int execInstruction(const table::Instruction & instruction, table::Object_Code & obj_file, table::Module & module){
    obj_file.push_back(table::inst_set[instruction.operation].opcode_num);
    module.header.bit_map += "0";
    // Introduzindo cada operando no vetor-linha de operação
    for (auto & token : instruction.operands){
        assert_isNotDigit(token, module, instruction.line);
        // Todos os símbolos ja foram definidos e serão enviados para
        // a tabela_de_uso ou tabela_de_definições
        // Adiconar simbolos não definidos na lista de erros
        bool tokenIsDefined = module.symbolsTable.find(token) != module.symbolsTable.end();
        if (tokenIsDefined){
            if (module.labelIsExtern(token)){
                module.insertLabelUseCase(token, obj_file.size());
                module.header.bit_map += "0";
            } else{
                module.header.bit_map += "1";
            }
            obj_file.push_back(module.getLabelAddr(token));
        }
    }
    assert_correctNumOperands(instruction, module);
    return table::inst_set[instruction.operation].size;
}