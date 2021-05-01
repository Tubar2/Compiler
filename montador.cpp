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
            if (argv[j][i] == '.' && i>3) break;
            filenames[j-1] += (argv[j][i]);
        }
    }
    // Criar um vetor que armazenará todos os módulos
    table::Assembly_Module_Set modules {};
    // Para cada arquivo de input, criaremos seu módulo e adicionaremos ao vetor de módulos
    for (int i=0; i<argc-1; i++){
        table::reset_flags();
        modules.push_back(firstPass(filenames[i] + ".asm"));
    }


    // Aplica o algoritmo de segunda passagem
    for (auto & module : modules) {
        correctDefinitionsTable(module);
        module.obj_code = secondPass(module);
    }

    assert_modulesHaveEnd(modules);

    // Vê se o arquivo .asm possui erros e imprime eles no terminal
    for (auto & module : modules){
        if (checkForErrors(module)) return 0;
    }

    // Cria o arquivo de saída .obj caso nào há erros
    for (int i =0;i<modules.size(); i++) {
        createObj(modules[i], filenames[i] + ".obj");
    }
    return 0;
}
