//
// Created by Ricardo Santos on 30/04/21.
//

#include "tables.hpp"

bool table::header_insertion_flag = true;
bool table::text_insertion_flag = false;

void table::reset_flags(){
    table::header_insertion_flag = true;
    table::text_insertion_flag = false;
}
