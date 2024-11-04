#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "../write_assembly.hpp"

string current_section_w;
std::ofstream file;

void add_line(string str, bool indent, bool comment){
    if (indent){
        file << "\t";
    }
    if (comment){
        file << COMMENT << " ";
    }
    file << str << "\n";
}

void set_section(string str){
    add_line();
    if (str != current_section_w) {
        add_line("." + str, false);
        current_section_w = str;
    }
}

void w_print(string str){
    if (str == "") return ;
}



