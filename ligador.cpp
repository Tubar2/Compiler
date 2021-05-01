//
// Created by Ricardo Santos on 01/05/21.
//

#include "aux/ligador/ligador_aux.hpp"

int main (int argc, char *argv[]){
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

    table::Object_Module_Set modules {};
    for (int i=0; i<argc-1; i++){
        modules.push_back(createObject(filenames[i] + ".obj"));
    }

    auto program = link_objects(modules);

    createObjectProgram(program, filenames[0] + ".obj2");

    return 0;
}


