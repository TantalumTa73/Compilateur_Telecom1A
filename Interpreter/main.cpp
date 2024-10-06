#include <iostream>

#include "json_reader.hpp"
#include "token.hpp"
#include "simplified_token.hpp"
#include "interpreter.hpp"
#include "exception.hpp"
#include "_test.hpp"


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
        return 1 ;
    }

    // testing();
    // return 0;
    /////////////////////

    JsonReader reader(filename);

    Token token = reader.readFile();
    // token.print();
    TkPtr simplified = simplify(token);
    Interpreter interpreter(simplified);
    interpreter.run();

    

    return 0;
}