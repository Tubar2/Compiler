//
// Created by Ricardo Santos on 09/03/21.
//

#include "montador_aux.hpp"
#include "../../database/tables.hpp"

// Checar se o label foi corretamente criado
table::Label checkLabel(table::Label & word, int lineCounter){
    // Verifica se o primeiro caractér é um digito
    if(isdigit(word[0])){
        table::errorsList.push_back({"Erro na nomenclatura do label '" + word + "'", "Léxico", lineCounter});
    }
    word.pop_back(); // Remove ':'
    // Verifica se o label possui menos que 50 caractéres
    if (word.length() > 50){
        table::errorsList.push_back({"Nome do label excede limite de caractéres", "Léxico", lineCounter});
    }
    return word;
}

// Separa uma string com operandos pela '.'
// "op1,op2" -> ["op1", "op2"]
table::Operands createOperands(const std::string& operands_string){
    // TODO: Alterar a função para popular as tabelas de definição e uso
    table::Operands operands {};
    std::istringstream iss {operands_string};
    std::string operand {};
    while (std::getline(iss, operand, ',')){
        if (operand == "text") {table::text_insertion_flag = true;}
        operands.push_back(operand);
    }
    return operands;
}

void pushInstruction(std::vector<table::Instruction> & instructions, const table::Instruction& instruction){
    instructions.push_back(instruction);
}

// Remove espaço em branco para evitar erros como
// ["  Label:" ou "   Label:   " ou "  Label  : "] -> "Label:  "
void correctLabel(table::Label & s){
    const std::string WHITESPACE = " \n\r\t\f\v";
    size_t start = s.find_first_not_of(WHITESPACE);
    s = (start == std::string::npos) ? "" : s.substr(start);

    auto foundLSpace = s.find(" :");
    auto foundFSpace = s.find(' ');
    if (foundLSpace != std::string::npos){
        auto erase = foundLSpace - foundFSpace + 1;
        s.erase(foundFSpace, erase);
    }
}


// Lê um arquivo de testo e popula um vetor com cada linha de instrução
table::Module readFile(const std::string& filename){
    // Abrindo arquivo para leitura e checando se foi aberto corretamente
    std::ifstream file {filename};
    if (!file) {
        // Arquivo não encotrado
        std::cerr << "Erro ao abrir arquivo" << std::endl;
        std::exit(1);
    }

    // Variáveis auxiliares
    std::string line, word;     // 'Line' será a linha do arquivo e 'word' cada palavra separada por espaçp
    int lineCounter{1};         // Contador de linha do arquivo texto
    table::Module data{}, text{}; // Semi-Módulos contendo ou a seção de dados (.data) ou de texto (.text)

    // Lendo arquvo linha por linha e salvando linha em 'line'
    while (std::getline(file, line)){
        correctLabel(line);              // Corrige labels que possuam espaço em branco
        std::istringstream iss{line};       // string-stream para leitura
        table::Instruction instruction {};  // Instrução para ser populada
        bool labelInLine = false;           // Variável auxiliar para indicar se houve label na linha
        // Espaços em branco são ignorados ao irem para a stream
        while (iss >> word) {
            // Checa por comentários
            if (word[0] == ';') { instruction.comment = word; break; }
            // Transforma cada palavra para minusculo
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            // Verifica se é um label ao procurar por ':'
            if (word.find(':')!= std::string::npos){
                instruction.label = checkLabel(word, lineCounter);
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
        if (table::text_insertion_flag){
            pushInstruction(text, instruction);
        } else {
            pushInstruction(data, instruction);
        }
    }
    // TODO: Verificar como será feita a seção de dados e texto, pois isso pode quebrar o programa
    // Conjunto de instruções = text + data (data no final)
    text.insert(text.end(), data.begin(), data.end());
    file.close(); // Fecha arquivo
    return text;
}

// Verifica se uma string é um dígito
bool is_decimal(std::string num){
    std::string::const_iterator it = num.begin();
    while (it != num.end() && (std::isdigit(*it) || *it == '-')) ++it;
    return !num.empty() && it == num.end();
}

int execDirective(const table::Operation& directive, const table::Operands& operands, std::vector<std::string> & line, int lineCounter){
    int numOperands = table::directive_set[directive];
    if (numOperands != operands.size()){
        table::errorsList.push_back({"Diretiva '" + directive + "' com número ilegal de operandos. Esperava: " +
                                 std::to_string(numOperands) + ". Recebeu: " + std::to_string(operands.size()),
                                 "Sintático", lineCounter});
    }
    if (directive == "space"){
        line.emplace_back("00");
        return 1;
    }
    if (directive == "const"){
        // Checar por 0 operandos ou um número não decimal
        if (operands.empty()){return 0;}
        if (!is_decimal(operands[0])) {
            table::errorsList.push_back({
                "Operando inválida na diretiva 'const'. Esperava decimal. Recebeu: '" + operands[0] + "'",
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
        if ( std::isdigit(token[0])){
            table::errorsList.push_back({
                "Tipo de operando '" + token + "' inválido",
                "Sintático",
                lineCounter
            });
        }
        // Adiconar simbolos não definidos em uma lista de pendencias
        if (table::symbolsTable.find(token) == table::symbolsTable.end()){
            if (!flag) {
                table::pendenciesList.push_back({lineCounter, line});
                flag = 1;
            }
            line->push_back(token);
            continue;
        }
        line->push_back(std::to_string(table::symbolsTable[token]));
    }
    if (operands.size() != table::inst_set[operation].size-1){
        table::errorsList.push_back({
            "Instrução '" + operation + "' com número ilegal de operandos. Esperava: " +
        std::to_string(table::inst_set[operation].size-1) + ". Recebeu: " + std::to_string(operands.size()),
        "Sintático", lineCounter});
    }
    return table::inst_set[operation].size;
}

std::vector<std::vector<std::string> *> secondPass(const std::vector<table::Instruction> & instructions){
    int posCounter{0};
    std::vector<std::vector<std::string> *> obj_file {};
    // Iterando sobre cada linha de instrução
    for (const auto& instruction : instructions){
        // Caso da operação ser uma Linha Vazia, só comentário ou só seção
        if (
            ( !instruction.comment.empty() && instruction.label.empty() && instruction.operation.empty() )  ||
            (instruction.operation == "section")                                                            ||
            ( instruction.comment.empty() && instruction.label.empty() && instruction.operation.empty() )
            ) { continue; }
        auto * line = new std::vector<std::string>{};
        // Checando a existência de label na instrução
        if (!instruction.label.empty()){
            // Procurando pela label na tabela de simbolos
            if (table::symbolsTable.find(instruction.label) == table::symbolsTable.end()){
                // Primeira aparição do label
                table::symbolsTable.insert({instruction.label, posCounter});
            } else {
                // Segunda aparição => Erro de redefinição
                table::errorsList.push_back({"Símbolo '" + instruction.label + "' redefinido", "Semântico",
                                         instruction.line});
            }
        }
        // Checando caso a operação da instrução existe
        if (instruction.operation.empty()){ continue;}
        if (table::inst_set.find(instruction.operation) == table::inst_set.end()){
            // Caso não existe, checar se é uma diretiva
            if (table::directive_set.find(instruction.operation) == table::directive_set.end()) {
                // Operação não identificada
                table::errorsList.push_back({"Operação '" + instruction.operation + "' não identificada", "Semântico", instruction.line});
            } else {
                // Operação existe na tabela de diretivas
                posCounter += execDirective( instruction.operation, instruction.operands, *line, instruction.line );
            }
        } else {
            // Operação existe na tabela de instruções
            posCounter += execInstruction(instruction.operation, instruction.operands, line, instruction.line);

        }
        obj_file.push_back(line);
    }
    return obj_file;
}

void removePendency(const std::vector<std::vector<std::string> *>& obj_file){
    for (auto pendency : table::pendenciesList){
        std::vector<std::string> pendentSymbols {};
        // Iterar sob cada símbolo pendente
        for (int i=pendency.pendency->size(); i>1; i--){
            // Se o simbolo está na tabela de símbolos substituir pela sua posição
            if (table::symbolsTable.find((*(pendency.pendency))[i-1]) != table::symbolsTable.end()){
                (*(pendency.pendency))[i-1] = std::to_string(table::symbolsTable[(*(pendency.pendency))[i-1]]);
            } else {
                pendentSymbols.push_back((*(pendency.pendency))[i-1]);
            }
        }
        if (!pendentSymbols.empty()){
            // Recuperar qua(l/is) símbolo/s não fo(i/ram) definido/s
            for (const auto& symbol : pendentSymbols){
                table::errorsList.push_back({"Símbolo '" + symbol + "' não definido", "Semântico", pendency.line});
            }
        }
    }
}

bool checkForErrors(){
    if (!table::errorsList.empty()){
        std::sort(table::errorsList.begin(), table::errorsList.end());
        for (const auto & error : table::errorsList){
            std::cout << std::left;
            std::cout << std::setfill(' ') << std::setw(21) << "Erro "+error.error_type +": ";
            std::cout << std::setfill(' ') << std::setw(13)<< "Linha: "+std::to_string(error.line) + " ";
            std::cout << error.error << std::endl;
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
        }
    }
    out_file.close();
}
