//
// Created by Ricardo Santos on 09/03/21.
//


#ifndef TRAB_SB_1_AUX_HPP
#define TRAB_SB_1_AUX_HPP
#include <fstream>
#include <iostream>
#include <sstream>
#include "../database/types.hpp"


void readFile(const std::string& filename, std::vector<table::Instruction> & instructions);
std::vector<std::vector<std::string> *> secondPass(const std::vector<table::Instruction>& instructions);
void removePendency(const std::vector<std::vector<std::string> *>& obj_file);
bool checkForErrors();
void createObj(const std::vector<std::vector<std::string> *>& obj_file, const std::string& name);

#endif //TRAB_SB_1_AUX_HPP
