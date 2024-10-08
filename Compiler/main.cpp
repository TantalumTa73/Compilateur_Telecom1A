#include <iostream>

#include "../Interpreter/json_reader.hpp"
#include "functions.hpp"
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
    std::string cfilename = argv[1];
    std::string jsonfilename = cfilename.substr(0, cfilename.size()) + ".json";
    JsonReader reader(jsonfilename);
    Token token = reader.readFile();
    Compiler compiler(token, cfilename);
    compiler.run();
    return 0;
}


