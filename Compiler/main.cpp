#include "compiler.hpp"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1; 
    }
    std::string cfilename = argv[1];
    Compiler compiler(cfilename);
    compiler.run();
    return 0;
}


