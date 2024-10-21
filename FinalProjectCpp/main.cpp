#include "JSON.hpp"
#include "token.hpp"
#include "interpreter.hpp"

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
    json->print();

    Tk token = Token::simplify(json) ;
    token->print();

    // Token* tk = new Token();
    // GStmt* gstmt = new GStmt();
    // Token* gstmt_tk = new GStmt();
    // GFunDef* gfun = new GFunDef();
    // GStmt* gfun_gstmt = new GFunDef();
    // Token* gfun_tk = new GFunDef();

    // tk->print();
    // gstmt->print();
    // gstmt_tk->print();
    // gfun->print();
    // gfun_gstmt->print();
    // gfun_tk->print();

    return 0;
}