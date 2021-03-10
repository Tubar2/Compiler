//
// Created by Ricardo Santos on 09/03/21.
//

#include "aux.hpp"
#include "../database/tables.hpp"

// Checar se o label foi corretamente criado
table::Label checkLabel(std::string & word, int lineCounter){
    if(isdigit(word[0])){
        table::errors.push_back({"Erro na nomenclatura do label '" + word + "'", "Sintático", lineCounter});
    }
    word.pop_back(); // Remove ':'
    return word;
}

table::Operands createOperands(const std::string& operands_string){
    table::Operands operands {};
    std::istringstream iss {operands_string};
    std::string operand {};
    while (std::getline(iss, operand, ',')){
        operands.push_back(operand);
    }
    return operands;
}

// Lê um arquivo de testo e popula um vetor com cada linha de instrução
void readFile(const std::string& filename, std::vector<table::Instruction> & instructions){
    // Abrindo arquivo para leitura e checando se foi aberto corretamente
    std::ifstream file {filename};
    if (!file) {
        // Arquivo não encotrado
        std::cerr << "Erro ao abrir arquivo" << std::endl;
        std::exit(1);
    }
    std::string line, word;
    int lineCounter{1}, endCounter{0};
    // Lendo arquvo linha por linha e salvando linha em 'line'
    while (std::getline(file, line)){
        std::istringstream iss{line};   // string stream para leitura
        table::Comment comment {};      // String de Comentários
        table::Label label {};           // String do label
        table::Operation operation {};  // String da operação
        table::Operands operands {};    // Vetor de operandos
        // Espaços em branco são ignorados ao passarem pelo stream
        while (iss >> word) {
            // Checa por comentários
            if (word[0] == ';') { comment = word; break; };
            // Transforma cada palavra para minusculo
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            // Verifica se é um label ao procurar por ':'
            if (word.find(':')!= std::string::npos){
                label = checkLabel(word, lineCounter);
            } else {
                // Caso não for um label ou um comentário então é uma parte da
                // estrutura da operação.
                if (operation.empty()){
                    operation = word;
                } else {
                    operands = createOperands(word);
                }
            }
        }
        // Popula o vetor com cada instrução devidamente estruturada
        instructions.push_back(table::Instruction{comment, label, operation, operands});
        lineCounter++;
    }
    file.close(); // Fecha arquivo
}

bool is_decimal(std::string num){
    std::string::const_iterator it = num.begin();
    while (it != num.end() && (std::isdigit(*it) || *it == '-')) ++it;
    return !num.empty() && it == num.end();
}

int execDirective(const table::Operation& directive, const table::Operands& operands, std::vector<std::string> & line, int lineCounter){
    int numOperands = table::directive_set[directive];
    if (numOperands != operands.size()){
        table::errors.push_back({"Diretiva '" + directive + "' com número ilegal de operandos. Esperava: " +
                                 std::to_string(numOperands) + ". Recebeu: " + std::to_string(operands.size()),
                                 "Sintático", lineCounter});
    }
    if (directive == "space"){
        // Substituir por "00" ao invés de "xx"
        line.emplace_back("xx");
        return 1;
    }
    if (directive == "const"){
        // Checar por 0 operandos ou um número não decimal
        if (operands.empty()){return 0;}
        if (!is_decimal(operands[0])) {
            table::errors.push_back({
                "Operando inválido na diretiva const. Esperava decimal. Recebeu: '" + operands[0] + "'",
                "Sintático",
                lineCounter
            });
            return 0;}
        line.push_back(operands[0]);
        return 1;
    }
    return 0;
}

int execInstruction(const table::Operation& operation, const table::Operands& operands, std::vector<std::string> * line, int lineCounter){
    int flag {0};
    line->push_back(table::inst_set[operation].opcode_num);
    // Introduzindo cada operando no vetor-linha de operação
    for (auto & token : operands){
        // Adiconar simbolos não definidos em uma lista de pendencias
        if (table::symbols.find(token) == table::symbols.end()){
            if (!flag) {
                table::pendencies.push_back({lineCounter, line});
                flag = 1;
            }
            line->push_back(token);
            continue;
        }
        line->push_back(std::to_string(table::symbols[token]));
    }
    if (operands.size() != table::inst_set[operation].size-1){
        table::errors.push_back({
            "Instrução '" + operation + "' com número ilegal de operandos. Esperava: " +
        std::to_string(table::inst_set[operation].size-1) + ". Recebeu: " + std::to_string(operands.size()),
        "Sintático", lineCounter});
    }
    return table::inst_set[operation].size;
}

std::vector<std::vector<std::string> *> secondPass(const std::vector<table::Instruction> & instructions){
    int lineCounter{1}, posCounter{0};
    std::vector<std::vector<std::string> *> obj_file {};
    // Iterando sobre cada linha de instrução
    for (const auto& instruction : instructions){
        // Caso da operação ser uma Linha VAzia, só comentário ou seção
        if (
            ( !instruction.comment.empty() && instruction.label.empty() && instruction.operation.empty() )  ||
            ( instruction.operation == "section" )                                                          ||
            ( instruction.comment.empty() && instruction.label.empty() && instruction.operation.empty() )
            ) { lineCounter++; continue; }
        auto * line = new std::vector<std::string>{"End", std::to_string(posCounter)};
        // Checando a existência de label na instrução
        if (!instruction.label.empty()){
            // Procurando pela label na tabela de simbolos
            if (table::symbols.find(instruction.label) == table::symbols.end()){
                // Primeira aparição do label
                table::symbols.insert({instruction.label, posCounter});
            } else {
                // Segunda aparição => Erro de redefinição
                table::errors.push_back({"Símbolo '" + instruction.label + "' redefinido", "Semântico",
                                         lineCounter});
            }
        }
        // Checando caso a operação da instrução existe
        if (instruction.operation.empty()){ lineCounter++;continue;}
        if (table::inst_set.find(instruction.operation) == table::inst_set.end()){
            // Caso não existe, checar se é uma diretiva
            if (table::directive_set.find(instruction.operation) == table::directive_set.end()) {
                // Operação não identificada
                table::errors.push_back({"Operação '" + instruction.operation + "' não identificada", "Semântico", lineCounter});
            } else {
                // Operação existe na tabela de diretivas
                posCounter += execDirective( instruction.operation, instruction.operands, *line, lineCounter );
            }
        } else {
            // Operação existe na tabela de instruções
            posCounter += execInstruction(instruction.operation, instruction.operands, line, lineCounter);

        }
        obj_file.push_back(line);
        lineCounter++;
    }
    return obj_file;
}

void removePendency(const std::vector<std::vector<std::string> *>& obj_file){
    for (auto pendency : table::pendencies){
        int flag {0}, i;
        // Iterar sob cada símbolo pendente
        // TODO: Otimizar para i>1
        for ( i=pendency.pendency->size(); i>0; i--){
            auto temp = (*(pendency.pendency))[i-1];
            // Se o simbolo está na tabela de símbolos substituir pela sua posição
            if (table::symbols.find((*(pendency.pendency))[i-1]) != table::symbols.end()){

                (*(pendency.pendency))[i-1] = std::to_string(table::symbols[(*(pendency.pendency))[i-1]]);
                flag = 1;
            }
        }
        if (!flag){
            // TODO: Recuperar qual símbolo não foi definido. Ideia: Colocar um else após o if símbolo está na tabela
            // TODO: Instrução com 2 simbolos não definidos recebe apenas 1. (eg. 'copy N3,N4' diz que apenas um símbolo não existe, não ambos)
            table::errors.push_back({"Símbolo não definido", "Semântico", pendency.line });
        }
    }
}

bool checkForErrors(){
    if (!table::errors.empty()){
        for (const auto & error : table::errors){
            std::cout << "Erro " << error.error_type << ": " << error.error  << " na linha "
            << std::to_string(error.line) << std::endl;
        }
        return true;
    }
    return false;
}

void createObj(const std::vector<std::vector<std::string> *>& obj_file, const std::string& name){
    std::ofstream out_file {name, std::ios::trunc};
    if (!out_file){
        std::cerr << "Error creating exit file " << name << std::endl;
        exit(1);
    } else {
        for (auto line : obj_file){
            for (auto &str : *line){
                out_file << str << " ";
            }
            out_file << std::endl;
        }
    }
    out_file.close();
}



















