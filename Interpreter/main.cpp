#include <unordered_map> // dictionary
#include <iostream>

#include "json_reader.hpp"
#include "token.hpp"
#include "interpreter.hpp"
#include "exception.hpp"

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    JsonReader reader(filename);
    Token token = reader.readFile();
    Interpreter interpreter(token);
    interpreter.run();

    

    return 0;
}