//
// Created by Ricardo Santos on 09/03/21.
//

#include "montador_aux.hpp"


table::Module firstPass(const std::string& filename){
    // Abrindo arquivo para leitura e checando se foi aberto corretamente
    std::ifstream file {filename};
    if (!file) {
        // Arquivo não encotrado
        std::cerr << "Erro ao abrir arquivo" << std::endl;
        std::exit(1);
    }
    // Criando o objeto do módulo que armazenará todas as informações a respeito do arquivo assembly
    table::Module module{};
    module.filename = filename;

    // Variáveis auxiliares
    std::string line, word;     // 'Line' será a linha do arquivo e 'word' cada palavra separada por espaçp
    int lineCounter{1}, posCounter_data{0}, posCounter_text{0};         // Contador de linha do arquivo texto
    table::Instructions_Set header{}, data{}, text{}; // Semi-Módulos contendo ou a seção de dados (.data) ou de texto (.text)

    // Lendo arquvo linha por linha e salvando linha em 'line'
    while (std::getline(file, line)){
        correctLabel(line);              // Corrige labels que possuam espaço em branco
        std::istringstream iss{line};       // string-stream para leitura
        table::Instruction instruction {};  // Instrução para ser populada
        // Espaços em branco são ignorados ao irem para a stream
        while (iss >> word) {
            // Checa por comentários
            if (word[0] == ';') { instruction.comment = word; break; }
            // Transforma cada palavra para minusculo
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            // Após a diretiva end, o programa para
            if (word == "end") {module.has_end = true; break;}
            // Verifica se é um label ao procurar por ':'
            if (word.find(':')!= std::string::npos){
                instruction.label = checkLabel(word, module, lineCounter);
            } else {
                // Caso não for um label ou um comentário então é uma parte da estrutura da operação
                if (instruction.operation.empty()){
                    instruction.operation = word;
                } else {
                    instruction.operands = createOperands(word);
                }
            }
        }
        if (word == "end"){break;}
        instruction.line = lineCounter++;   // Adiciona à estrutura da instrução, sua linha de ocorrência no arquivo
        // Popula o semi-módulo com cada instrução devidamente estruturada
        if (table::header_insertion_flag){
            defineBegindExternPublic(instruction, module);
            header.push_back(instruction);
        }else if (table::text_insertion_flag){
            defineLabels(instruction, module, posCounter_text);
            text.push_back(instruction);
        } else {
            defineVariables(instruction, module, posCounter_data);
            data.push_back(instruction);
        }
    }
    correctDataAddr(data,module, posCounter_text);

    // Conjunto de instruções = header + .text + .data
    text.insert(text.end(), data.begin(), data.end());
    header.insert(header.end(), text.begin(), text.end());

    module.instructions = header;
    file.close(); // Fecha arquivo
    return module;
}

void correctDefinitionsTable(table::Module & module){
    for (auto & val : module.definitionsTable){
        val.second = module.symbolsTable[val.first].addr;
    }
}

table::Object_Code secondPass(table::Module & module){
    int posCounter{0};
    table::Object_Code obj_file {};
    // Iterando sobre cada linha de instrução
    for (const auto & instruction : module.instructions){
        // Caso da operação ser uma só comentário, só seção, Linha Vazia ou header, respectivamento
        if (
            ( !instruction.comment.empty() && instruction.label.empty() && instruction.operation.empty() )  ||
            ( instruction.operation == "section")                                                            ||
            ( instruction.comment.empty() && instruction.label.empty() && instruction.operation.empty() )   ||
            ( instruction.operation == "begin" || instruction.operation == "extern" || instruction.operation == "public" || instruction.operation == "end")
            ) { continue; }
        std::vector<std::string> line = {};
        // Checando caso a linha faça alguma operação
        if (instruction.operation.empty()){ continue;}
        // Vendo se a instrução é uma instrução
        bool isInstruction = table::inst_set.find(instruction.operation) != table::inst_set.end();
        if (!isInstruction){
            // Caso não existe, checar se é uma diretiva
            bool isDirective = table::directive_set.find(instruction.operation) != table::directive_set.end();
            if (!isDirective) {
                assert_isNotDirectiveOrOperation(instruction, module);
            } else {
                // Operação existe na tabela de diretivas
                posCounter += execDirective( instruction, obj_file, module);
            }
        } else {
            // Operação existe na tabela de instruções
            posCounter += execInstruction(instruction, obj_file, module);

        }
    }
    return obj_file;
}


bool checkForErrors(table::Module & module){
    if (!module.errorsList.empty()){
        std::sort(module.errorsList.begin(), module.errorsList.end());
        for (const auto & error : module.errorsList){
            std::cout << std::left;
            std::cout << std::setfill(' ') << std::setw(21) << "Erro "+error.error_type +": ";
            std::cout << std::setfill(' ') << std::setw(13)<< "Linha: "+std::to_string(error.line) + " ";
            std::cout << error.error << std::endl;
        }
        return true;
    }
    return false;
}

void createObj(const table::Module & module, const std::string& name){
    std::ofstream out_file {name, std::ios::trunc};
    if (!out_file){
        std::cerr << "Error creating exit file " << name << std::endl;
        exit(1);
    } else {
        out_file << "H: " << module.header.name << "\n";
        out_file << "H: " << module.obj_code.size() << "\n";
        out_file << "R: " <<  module.header.bit_map << "\n";
        for (auto & use_case : module.usesTable){
            out_file << "U: " << use_case.label << "," << use_case.addr << "\n";
        }
        for (auto & definedSymbol : module.definitionsTable){
            out_file << "D: " << definedSymbol.first << "," << definedSymbol.second << "\n";
        }
        out_file << "T: ";
        for (auto code : module.obj_code){
            out_file << code << " ";
        }
    }
    out_file.close();
}
