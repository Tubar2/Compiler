#include "aux_functions/aux.hpp"


#define FPATH "../test_2.asm"

int main() {
    // Criar um vetor com linhas de Instruções
    std::vector<table::Instruction> instructions {};
    // TODO: Correct filename to use argc and argv
    // Popula o vetor de instruções
    readFile(FPATH, instructions);

    // Aplica o algoritmo de segunda passagem modificado
    auto obj_file = secondPass(instructions);

    // Substitui os símbolos que não haviam sido definidos ainda
    removePendency(obj_file);

    // Vê se o arquivo .asm possía erros e imprime eles no terminal
    if (checkForErrors()) return 0;

    // Cria o arquivo de saída .obj caso nào há erros
    createObj(obj_file, "../montador.obj");

    for (auto line : obj_file){
        for (auto &str : *line){
            std::cout << str << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
