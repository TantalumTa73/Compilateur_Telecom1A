#include <vector>
#include <iostream>
#include <fstream>
#include "token.hpp"
#include "json_reader.hpp"


void JsonReader::readFile(){
    std::ifstream file = std::ifstream(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << "\n";
        return ;
    }

    int i = 0;
    std::string word;
    std::string word_last;
    std::string word_last_last;
    char c = file.get();
    while ( ! file.eof() ) {
        word = "";
        c = file.get();
        while (c != ',' and ! file.eof()) {
            word += c;
            c = file.get();
        }
        std::cout << word << "\n";
    }

    file.close();

    return ;
}

