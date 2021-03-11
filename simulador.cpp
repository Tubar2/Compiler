//
// Created by Ricardo Santos on 10/03/21.
//

#include <fstream>
#include <sstream>
#include "aux/simulador/simulador_aux.hpp"

#define FPATH "../tests/test_1/montador.obj"

int main(){
    // TODO: Usar argc e argv
    // Abrindo arquivo objeto para leitura
    std::ifstream file {FPATH};
    if (!file) {
        // Arquivo não encotrado
        std::cerr << "Erro ao abrir arquivo" << std::endl;
        std::exit(1);
    }
    std::string line, lixo;
    int num {};
    std::vector<int> memory{}, data{};
    // Lendo arquvo linha por linha e salvando linha em 'line'
    while (std::getline(file, line)){
        std::istringstream iss {line};
        // Remove o 'End xx'
        iss >> lixo >> lixo;
        bool flag {false};
        while (iss >> num){
            memory.push_back(num);
            flag = true;
        }
        if (!flag){
            // Início da seção de texto
            memory.push_back(infinity);
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