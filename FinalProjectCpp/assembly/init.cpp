#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "write_assembly.hpp"

void init(){

    filesystem::path path = file_name ;
    path.replace_extension(".s");

    v_cout << "Output file: " << path.string() << "\n";

    file.open(path.string(), std::ios::out);

    def_operators();
    
    w_init_template();
}

void w_init_template(){
    std::ifstream src(TEMPLATE);
    std::string line;
    while (getline(src, line)) {
        add_line(line, false, false);
    }
    src.close();
}
