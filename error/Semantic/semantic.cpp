//
// Created by Ricardo Santos on 30/04/21.
//

#include "../error_handling.hpp"

void assert_isNotDirectiveOrOperation(const table::Instruction & instruction, table::Assembly_Module & module){
    module.pushError({
        "Operação '" + instruction.operation + "' não identificada",
        "Semântico",
        instruction.line
    });
}