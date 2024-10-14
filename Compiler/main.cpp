#include <iostream>

#include "json_reader.hpp"
#include "functions.hpp"
#include "exception.hpp"
#include "token.hpp"
#include "compiler.hpp"
#include "data.hpp"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        v_cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1; 
    }
    std::string cfilename = argv[1];
    std::string jsonfilename = cfilename.substr(0, cfilename.size() - 1) + "json";
    JsonReader reader(jsonfilename);
    Token token = reader.readFile();
    Compiler compiler(token, cfilename);
    compiler.run();
    return 0;
}


