//
// Created by Ricardo Santos on 01/05/21.
//
#include "types.hpp"



std::map<table::Label, table::Address> table::Object_Module::globalDefinitionsTable {};
std::vector<int> table::Object_Module::correction_factors {0};
int table::Object_Module::cur_number {1};
