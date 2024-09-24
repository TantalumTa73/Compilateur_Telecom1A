#include <unordered_map> // dictionary
#include <iostream>

#include "json_reader.hpp"
#include "token.hpp"
#include "interpreter.hpp"
#include "exception.hpp"

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        v_cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    } else if (argc > 2) {
        verbose = true;
        v_cout << "Verbose mode" << std::endl;
    }

    std::string filename = argv[1];
    JsonReader reader(filename);
    Token token = reader.readFile();
    Interpreter interpreter(token);
    interpreter.run();

    

    return 0;
}