#include "JSON.hpp"
#include "token.hpp"
#include "execution.hpp"

extern int verbose;

int main(int argc, char** argv) {
    if (argc < 2) {
        string msg = "Usage: " + string(argv[0]) + " <filename>";
        ERROR(msg);
    }
    
    if (argc > 2 && string(argv[2]) == "-v") verbose = 1;
    else if (argc > 2 && string(argv[2]) == "-vv") verbose = 2;
    else verbose = 0;
    

    std::cout << "Start execution of " << argv[1] << "\n";
    std::cout << "Verbose level: " << verbose << "\n\n";

    JSON* json = new JSON(argv[1]);
    // json->print();

    Tk token = Token::simplify(json) ;
    token->print();
    Root* root = dynamic_cast<Root*>(token);

    Execution execution = Execution(root);

    return 0;
}