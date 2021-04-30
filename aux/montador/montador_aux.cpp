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

    // Variáveis auxiliares
    std::string line, word;     // 'Line' será a linha do arquivo e 'word' cada palavra separada por espaçp
    int lineCounter{1}, posCounter{0};         // Contador de linha do arquivo texto
    table::Module module{};
    // TODO: Adicionar um header{} para diretivas e instruções begin, public e extern
    table::Instructions_Set data{}, text{}; // Semi-Módulos contendo ou a seção de dados (.data) ou de texto (.text)

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
        instruction.line = lineCounter++;   // Adiciona à estrutura da instrução, sua linha de ocorrência no arquivo
        // Popula o semi-módulo com cada instrução devidamente estruturada
        if (!instruction.label.empty()){
            fPass_defineLabel(instruction, module, posCounter);
        }
        if (!instruction.operation.empty()){
            fPass_defineOperation(instruction, module, posCounter);
        }
        if (table::text_insertion_flag){
            text.push_back(instruction);
        } else {
            data.push_back(instruction);
        }
    }
    // TODO: Verificar como será feita a seção de dados e texto, pois isso pode quebrar o programa
    // Conjunto de instruções = text + data (data no final)
    text.insert(text.end(), data.begin(), data.end());
    module.instructions = text;
    file.close(); // Fecha arquivo
    return module;
}

table::Object_Code secondPass(table::Module & module){
    int posCounter{0};
    table::Object_Code obj_file {};
    // Iterando sobre cada linha de instrução
    for (const auto & instruction : module.instructions){
        // Caso da operação ser uma só comentário, só seção ou Linha Vazia, respectivamento
        if (
            ( !instruction.comment.empty() && instruction.label.empty() && instruction.operation.empty() )  ||
            (instruction.operation == "section")                                                            ||
            ( instruction.comment.empty() && instruction.label.empty() && instruction.operation.empty() )
            ) { continue; }
        std::vector<std::string> line = {};
        // Checando caso a linha faça alguma operação
        if (instruction.operation.empty()){ continue;}
        // Vendo se a instrução é uma instrução
        bool isInstruction = table::inst_set.find(instruction.operation) != table::inst_set.end();
        if (!isInstruction){
            // Caso não existe, checar se é uma diretiva
            bool isDirective = table::inst_set.find(instruction.operation) != table::inst_set.end();
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

//void removePendency(const std::vector<std::vector<std::string> *>& obj_file){
//    for (auto pendency : table::pendenciesList){
//        std::vector<std::string> pendentSymbols {};
//        // Iterar sob cada símbolo pendente
//        for (int i=pendency.pendency->size(); i>1; i--){
//            // Se o simbolo está na tabela de símbolos substituir pela sua posição
//            if (table::symbolsTable.find((*(pendency.pendency))[i-1]) != table::symbolsTable.end()){
//                (*(pendency.pendency))[i-1] = std::to_string(table::symbolsTable[(*(pendency.pendency))[i-1]]);
//            } else {
//                pendentSymbols.push_back((*(pendency.pendency))[i-1]);
//            }
//        }
//        if (!pendentSymbols.empty()){
//            // Recuperar qua(l/is) símbolo/s não fo(i/ram) definido/s
//            for (const auto& symbol : pendentSymbols){
//                table::errorsList.push_back({"Símbolo '" + symbol + "' não definido", "Semântico", pendency.line});
//            }
//        }
//    }
//}
//
//bool checkForErrors(){
//    if (!table::errorsList.empty()){
//        std::sort(table::errorsList.begin(), table::errorsList.end());
//        for (const auto & error : table::errorsList){
//            std::cout << std::left;
//            std::cout << std::setfill(' ') << std::setw(21) << "Erro "+error.error_type +": ";
//            std::cout << std::setfill(' ') << std::setw(13)<< "Linha: "+std::to_string(error.line) + " ";
//            std::cout << error.error << std::endl;
//        }
//        return true;
//    }
//    return false;
//}
//
//void createObj(const std::vector<std::vector<std::string> *>& obj_file, const std::string& name){
//    std::ofstream out_file {name, std::ios::trunc};
//    if (!out_file){
//        std::cerr << "Error creating exit file " << name << std::endl;
//        exit(1);
//    } else {
//        for (auto line : obj_file){
//            for (auto &str : *line){
//                out_file << str << " ";
//            }
//        }
//    }
//    out_file.close();
//}
