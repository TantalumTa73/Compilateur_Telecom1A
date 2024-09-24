#include <iostream>

#include "../Interpreter/json_reader.hpp"
#include "../Interpreter/functions.hpp"
#include "../Interpreter/exception.hpp"
#include "../Interpreter/token.hpp"
#include "compiler.hpp"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        v_cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1; 
    }
    std::string filename = argv[1];
    JsonReader reader(filename);
    Token token = reader.readFile();
    Compiler compiler(token, filename);
    compiler.run();
    return 0;
}


