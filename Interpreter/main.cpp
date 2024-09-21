#include <unordered_map> // dictionary
#include <iostream>

#include "json_reader.hpp"

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    JsonReader reader(filename);
    reader.readFile();

    return 0;
}