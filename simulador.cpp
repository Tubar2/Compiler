//
// Created by Ricardo Santos on 10/03/21.
//

#include <fstream>
#include <sstream>
#include "aux/simulador/simulador_aux.hpp"

#define FPATH "../montador.obj"

int main(){
    // TODO: Usar argc e argv
    // Abrindo arquivo objeto para leitura
    std::ifstream file {FPATH};
    if (!file) {
        // Arquivo não encotrado
        std::cerr << "Erro ao abrir arquivo" << std::endl;
        std::exit(1);
    }
    std::vector<int> memory{};
    std::string line, lixo;
    int num;
    // Lendo arquvo linha por linha e salvando linha em 'line'
    while (std::getline(file, line)){
        std::istringstream iss {line};
        // Remove o 'End xx'
        iss >> lixo >> lixo;
        while (iss >> num){
            memory.push_back(num);
        }
    }
//    int i {0};
//    for (const auto & code : memory){
//        std::cout << i << "-" << code << std::endl;
//        i++;
//    }
    runProgram(memory);

    return 0;
}