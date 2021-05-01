//
// Created by Ricardo Santos on 01/05/21.
//

#ifndef TRAB_SB_1_LIGADOR_AUX_HPP
#define TRAB_SB_1_LIGADOR_AUX_HPP

#include <iostream>
#include <array>
#include <string>
#include <fstream>
#include "../../database/types.hpp"

table::Object_Module createObject(const std::string& filename);
table::Object_Code link_objects(table::Object_Module_Set & modules);
void createObjectProgram(const table::Object_Code &prog, const std::string& filename);

#endif //TRAB_SB_1_LIGADOR_AUX_HPP
