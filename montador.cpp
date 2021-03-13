#include "aux/montador/montador_aux.hpp"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Número de argumentos inválidos" << std::endl;
        exit(1);
    }
    std::string filename;
    for (int i = 0; i < strlen(argv[1]); ++i) {
        if (argv[1][i] == '.') break;
        filename += (argv[1][i]);
    }
    // Criar um vetor com linhas de Instruções
    std::vector<table::Instruction> instructions {};
    // Popula o vetor de instruções
    instructions = readFile(filename + ".asm");

    // Aplica o algoritmo de segunda passagem modificado
    auto obj_file = secondPass(instructions);

    // Substitui os símbolos que não haviam sido definidos ainda
    removePendency(obj_file);

    // Vê se o arquivo .asm possía erros e imprime eles no terminal
    if (checkForErrors()) return 0;

    // Cria o arquivo de saída .obj caso nào há erros
    createObj(obj_file, filename+".obj");

    return 0;
}
