//
// Created by Ricardo Santos on 10/03/21.
//

#include "simulador_aux.hpp"
#include "../../database/tables.hpp"

int ACC {0};
int PC {0};
//uint16_t memory[216];
bool exec(int opcode, std::vector<int>& memory) {
    switch (opcode) {
        case 1:                             // ADD
            ACC += memory[memory[PC+1]];    // ACC <- ACC + mem(op)
            break;
        case 2:                             // SUB
            ACC -= memory[memory[PC+1]];    // ACC <- ACC - mem(op)
            break;
        case 3:                             // MUL
            ACC *= memory[memory[PC+1]];    // ACC <- ACC * mem(op)
            break;
        case 4:                             // DIV
            ACC /= memory[memory[PC+1]];    // ACC <- ACC / mem(op)
            break;
        case 5:                             // JMP
            PC = memory[PC+1];              // PC <- op
            return true;
        case 6:                             // JMPN
            if (ACC < 0) {                  // Se ACC < 0
                PC = memory[PC+1];          // PC <- op
                return true;
            }
            break;
        case 7:                             // JMPP
            if (ACC > 0) {                  // Se ACC > 0
                PC = memory[PC+1];          // PC <- op
                return true;
            }
            break;
        case 8:                             // JMPZ
            if (!ACC){                      // Se ACC == 0
                PC = memory[PC+1];          // PC <- op
                return true;
            }
            break;
        case 9:                             // COPY
            memory[memory[PC+2]] = memory[memory[PC+1]];    // mem(op2) <- mem(op1)
            break;
        case 10:                        // LOAD
            ACC = memory[memory[PC+1]];         // ACC <- mem(op)
            break;
        case 11:                        // STORE
            memory[memory[PC+1]] = ACC;         // mem(op) <- ACC
            break;
        case 12:                        // INPUT
            std::cin >> memory[memory[PC+1]];   // mem(op) <- entrada
            break;
        case 13:                         // OUTPUT
            std::cout << memory[memory[PC+1]] << std::endl; // saída <- mem(op)
            break;
        case 14:                         // STOP
            return false;

        default:
            break;
    }
    PC += table::inst_size[opcode];
    return true;
}

void runProgram( std::vector<int>& memory){
    while ( exec(memory[PC], memory) );
}