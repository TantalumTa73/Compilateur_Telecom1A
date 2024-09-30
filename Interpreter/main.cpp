#include <unordered_map> // dictionary
#include <iostream>

#include "json_reader.hpp"
#include "json_simplifier.hpp"
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

    if (filename.find(".json") == std::string::npos) {
        v_cout << "Invalid file extension\n";
        v_cout << "Invalid file extension\n";
        v_cout << "Invalid file extension\n";
        v_cout << "Invalid file extension\n\n";
    }

    JsonReader reader(filename);
    Token token = reader.readFile();
    Token simplified = simplify(token);
    Interpreter interpreter(simplified);
    interpreter.run();

    

    return 0;
}