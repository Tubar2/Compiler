#include <array>
#include "aux/montador/montador_aux.hpp"


int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 4) {
        std::cerr << "Número de argumentos inválidos" << std::endl;
        exit(1);
    }
    // Lê cada arquivo fornecido e remove o final ".asm"
    std::array<std::string, 3> filenames;
    for(int j = 1; j<argc; j++) {
        for (int i = 0; i < strlen(argv[j]); ++i) {
            if (argv[j][i] == '.') break;
            filenames[j-1] += (argv[j][i]);
        }
    }
    // Criar um vetor que armazenará todos os módulos
    table::Module_Set modules {};
    // Para cada arquivo de input, criaremos seu módulo e adicionaremos ao vetor de módulos
    for (int i=0; i<argc; i++){
        modules.push_back(readFile(filenames[i] + ".asm"));
    }

    // Aplica o algoritmo de segunda passagem modificado
    for (auto & module : modules) {
//        auto obj_file = secondPass(instructions);
        auto obj_file = secondPass(module);
    }

    // Substitui os símbolos que não haviam sido definidos ainda
    removePendency(obj_file);

    // Vê se o arquivo .asm possía erros e imprime eles no terminal
    if (checkForErrors()) return 0;

    // Cria o arquivo de saída .obj caso nào há erros
    createObj(obj_file, filename + ".obj");

    return 0;
}
