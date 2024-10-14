#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>
#include "jsonReader.hpp"
#include "token.hpp"

#define print_indent(indent) for (int i = 0; i < indent; i++) cout << "\t";


void JsonReader::add_attribute(string name, string value, Token* ptr){

    // print_indent(indent);
    if (tokens.size() == 0){
        std::cerr << "Error in add_attribute: no token in tokens\n";
        return ;
    }

    // if (value == ""){
    //     cout << "Adding attribute : " << type_name(tokens.back()->type) ;
    //     cout << "." << name << " at " << ptr << " " << type_name(ptr->type) << "\n";
    // }
    
    if (name == "type"){

        if (value == "file") tokens.push_back(new Root());
        else if (value == "stmt list") tokens.push_back(new Scope());
        else if (value == "fundef") tokens.push_back(new FunDef());
        else if (value == "for") tokens.push_back(new LoopFor());

        else if (value == "stmt") tokens.push_back(new Stmt(STMT));
        else if (value == "expr") tokens.push_back(new Expr(EXPR));
        else if (value == "const") tokens.push_back(new Litteral(LITTERAL));
        else if (value == "left_value") tokens.push_back(new LeftVal(UNDEFINED));

        else if (value == "return") tokens.push_back(new Return());
        else if (value == "varset") tokens.push_back(new VarSet());
        // if, elif, else, while

        else if (value == "var") tokens.push_back(new Var());
        // else if (value == "") tokens.push_back(new ListElm());

        else if (value == "moins") tokens.push_back(new Uniop());
        else if (value == "not") tokens.push_back(new Uniop());
        else if (value == "binop") tokens.push_back(new Binop());
        else if (value == "array access") tokens.push_back(new ListGet());
        else if (value == "call") tokens.push_back(new Call());
        // else if (value == "") tokens.push_back(new VarGet());

        else if (value == "list") tokens.push_back(new List());
        else if (value == "int") tokens.push_back(new Int());
        // else if (value == "") tokens.push_back(new Float());
        else if (value == "string") tokens.push_back(new String());
        else if (value == "bool") tokens.push_back(new Bool());
        else if (value == "none") tokens.push_back(new None());

        else tokens.push_back(new Token());

        // cout << "Adding token of type " << value << " at " << tokens.back() << "\n";
        // for (auto tk : tokens) cout << tk->type << " "; cout << "\n";

    } 
    
    else if (name == "start_line") tokens.back()->pos.start_line = stoi(value);
    else if (name == "start_char") tokens.back()->pos.start_char = stoi(value);
    else if (name == "end_line") tokens.back()->pos.end_line = stoi(value);
    else if (name == "end_char") tokens.back()->pos.end_char = stoi(value);

    else if (tokens.back()->type == UNDEFINED){
        std::cerr << "Error in file: undefined last token (add_attribute)\n";
    } else if (tokens.back()->type == SCOPE){
        Scope* tk = (Scope*) tokens.back();
        if      (name == "pos") tk->pos = Pos();
        else std::cerr << "Bad attribute to Scope: " << name << "\n";
    
    // } else if (tokens.back()->type == POS){
    //     Pos* tk = (Pos*) tokens.back();
    //     if      (name == "start_line") tk->start_line = stoi(value);
    //     else if (name == "start_char") tk->start_char = stoi(value);
    //     else if (name == "end_line") tk->end_line = stoi(value);
    //     else if (name == "end_char") tk->end_char = stoi(value);
    //     else std::cerr << "Bad attribute to Pos: " << name << "\n";
    
    } else if (tokens.back()->type == ROOT){
        Root* tk = (Root*) tokens.back();
        if      (name == "pos") tk->pos = Pos();
        else if (name == "[i]") {
            tk->funs.push_back((Token*) ptr); 
            // cout << "New obj in Root :" << type_name(ptr->type)<< " at ("<< ptr << ")\n";
        }
        else std::cerr << "Bad attribute to Root: " << name << "\n";

    } else if (tokens.back()->type == STMT){
        Stmt* tk = (Stmt*) tokens.back();
        if      (name == "pos") tk->pos = Pos();
        else if (name == "stmt") {
            tk->next = ptr; 
            // cout << "New obj in Stmt :" << type_name(ptr->type)<< " at ("<< ptr << ")\n";
            }
        else std::cerr << "Bad attribute to Stmt: " << name << "\n";

    } else if (tokens.back()->type == EXPR){
        Expr* tk = (Expr*) tokens.back();
        if      (name == "pos") tk->pos = Pos();
        else if (name == "value") {
            tk->next = ptr; 
            // cout << "New obj in Expr :" << type_name(ptr->type)<< " at ("<< ptr << ")\n";
            }
        else std::cerr << "Bad attribute to Expr: " << name << "\n";

    } else if (tokens.back()->type == LITTERAL){
        Litteral* tk = (Litteral*) tokens.back();
        if      (name == "pos") tk->pos = Pos();
        else if (name == "value") {
            tk->next = ptr; 
            // cout << "New obj in Litteral :" << type_name(ptr->type)<< " at ("<< ptr << ")\n";
            }
        else std::cerr << "Bad attribute to Litteral: " << name << "\n";

    } else if (tokens.back()->type == INT){
        Int* tk = (Int*) tokens.back();
        if      (name == "pos") tk->pos = Pos();
        else if (name == "value") tk->value = stoi(value);
        else std::cerr << "Bad attribute to Int: " << name << "\n";
    
    } else {
        std::cerr << "Error : unknow type " << type_name(tokens.back()->type) << "\n";
    }

    // "stmt","expr","const","int",
    // STMT EXPR LITTERAL INT

    return ;
}

Root JsonReader::readFile(){

    std::ifstream file = std::ifstream(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << "\n";
        Root r = Root();
        r.type = UNDEFINED;
        return r;
    }
    cout << "\n";

    vector<string> attributes = vector<string>();
    tokens = vector<Token*>();

    Root root = Root();

    
    std::string name ;
    std::string value ;
    bool is_name ;
    char c ;
    int indent = 0;

    while ( ! file.eof() ) {
        c = file.get();
        // Token* ptk = tokens.back();
        
        if (c == '{' || c == '['){
            print_indent(indent);
            // if (name != "pos")
            cout << name << " : " <<((c=='{') ? " {" : " [") << "\n";
            if (indent == 0){
                attributes.push_back("root");
                tokens.push_back(&root);
            } else if (name != ""){
                attributes.push_back(name);
            } else { 
                attributes.push_back("[i]");
            }
            indent++;
            name = "" ;
            value = "" ;
            is_name = true ;
            // v_cout << "New object at " << token_ptr << ", parent: " << token_ptr->parent << "\n";
        }
        else if (c == ',' || c == '}' || c == ']'){
            // if (name != "start_line" && name != "start_char" && name != "end_line" && name != "end_char" && name != ""){
            
            if (name != ""){
                print_indent(indent);
                cout << name << " : " << value << "\t";
                for (string att : attributes) cout << att << ".";
                cout << "\n";
                add_attribute(name, value, nullptr);
            }

            name = "";
            value = "";
            is_name = true;
            
            if (c == '}' || c == ']'){

                if (attributes.size() == 0 || tokens.size() == 0){
                    std::cerr << "Error in readfile: no token ";
                    std::cerr << attributes.size() << ", " << tokens.size() << "\n";
                    break;
                }

                // cout << "ending : " << attributes.size() << ", " << tokens.size() << "\n";
                string att = attributes.back();
                Token* tk = tokens.back();
                attributes.pop_back();
                tokens.pop_back();

                if (att == "root"){
                    cout << "End of file\n";
                    tokens.push_back(tk);
                    break;
                }

                indent--;
                print_indent(indent);
                cout << "end of \'" << att << "\' " ;
                cout << ((c=='}') ? "}" : "]") << "\n";
                add_attribute(att, "", tk);
            }
        }
        else if (c == ':' && is_name) {
            is_name = false;
        }
        else if (c == ':' && ! is_name) {
            std::cerr << "Error in file: bad json\n";
            
            break;
        }
        else if (c != '\n' && c != '\t' && c != '\"' && c != ' '){
            if (is_name) name += c;
            else value += c;
        }        
    }

    file.close();

    cout << "Printing tokens\n";
    for (Token* tk : tokens){
        tk->print();
    }
    

    // v_cout << "End at object : " << token_ptr << " (" << (token_ptr==&root)<< ")\n";


    return root;
}

