//
// Created by Ricardo Santos on 01/05/21.
//


#include <sstream>
#include "ligador_aux.hpp"

std::vector<std::string> splitLabel(std::string word){
    std::vector<std::string> tokens {};

    size_t pos = word.find(',');
    tokens.push_back(word.substr(0,pos));
    word.erase(0, pos+1);
    tokens.push_back(word);
    return tokens;
}

table::Object_Module createObject(const std::string& filename){
    // Abrindo arquivo para leitura e checando se foi aberto corretamente
    std::ifstream file {filename};
    if (!file) {
        // Arquivo não encotrado
        std::cerr << "Erro ao abrir arquivo" << std::endl;
        std::exit(1);
    }
    table::Object_Module module {};
    module.module_number = table::Object_Module::cur_number++;
    std::string line, word, trash;     // 'Line' será a linha do arquivo e 'word' cada palavra separada por espaço

    while (std::getline(file, line)){
        std::istringstream iss{line};       // string-stream para leitura
        while (iss >> word) {
            if (word == "H:"){
                int correction_factor;
                if (iss >> correction_factor){
                    table::Object_Module::correction_factors.push_back(correction_factor);
                }
                break;
            }
            if (word == "R:"){
                 iss >> module.bit_map;
                break;
            }
            if (word == "U:"){
                iss >> word;
                auto tokens = splitLabel(word);
                module.insertLabelUseCase(tokens[0], std::stoi(tokens[1]));
                break;
            }
            if (word == "D:"){
                iss >> word;
                auto tokens = splitLabel(word);
                module.defineLabel(tokens[0], std::stoi(tokens[1]));
                break;
            }
            if (word == "T:"){
                while (iss >> word){
                    module.obj_code.push_back(std::stoi(word));
                }
            }
        }
    }


    return module;
}

table::Object_Code link_objects(table::Object_Module_Set & modules) {
    table::Object_Code program {};
    for (auto & module : modules){
        for (const auto & useCase : module.usesTable){
            module.obj_code[useCase.addr] = table::Object_Module::globalDefinitionsTable[useCase.label];
        }
        for (int i=0; i<module.bit_map.length(); i++){
            int reloc = (module.bit_map[i]-0x30);
            if (reloc == 1){
                module.obj_code[i] += table::Object_Module::correction_factors[module.module_number-1];
            }
        }
        program.insert(program.end(), module.obj_code.begin(), module.obj_code.end());
    }
    return program;
}

void createObjectProgram(const table::Object_Code &prog, const std::string& filename) {
    std::ofstream out_file {filename, std::ios::trunc};
    if (!out_file){
        std::cerr << "Error creating exit file " << filename << std::endl;
        exit(1);
    } else {
        for (auto code : prog){
            out_file << code << " ";
        }
        out_file << "\n";
    }
}