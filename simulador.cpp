//
// Created by Ricardo Santos on 10/03/21.
//

#include <fstream>
#include <sstream>
#include "aux/simulador/simulador_aux.hpp"


int main(int argc, char *argv[]){
    if (argc != 2){
        std::cerr << "Número de argumentos inválidos" << std::endl;
        exit(1);
    }
    // Abrindo arquivo objeto para leitura
    std::ifstream file {argv[1]};
    if (!file) {
        // Arquivo não encotrado
        std::cerr << "Erro ao abrir arquivo" << std::endl;
        std::exit(1);
    }
    std::string line;
    int num {};
    std::vector<int> memory{};
    // Lendo arquvo linha por linha e salvando linha em 'line'
    std::getline(file, line);
    std::istringstream iss {line};
    while (iss >> num){
        memory.push_back(num);
    }

    runProgram(memory);

    return 0;
}