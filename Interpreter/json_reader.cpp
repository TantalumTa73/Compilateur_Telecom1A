#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>
#include "json_reader.hpp"
#include "token.hpp"


Token JsonReader::readFile(){

    std::ifstream file = std::ifstream(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << "\n";
        return Token();
    }

    Token root = Token(0, 0, -1, -1);
    root.set_attribute("name", "__root__");
    root.set_attribute("action", "gfundef");
    Token *token_ptr = &root;

    // v_cout << "Main at " << token_ptr << "\n";
    
    std::string name ;
    std::string value ;
    bool is_name ;
    char c ;

    while ( ! file.eof() ) {
        c = file.get();
        
        if (c == '{'){
            token_ptr->add_child(Token());
            token_ptr = &token_ptr->childs.back();
            name = "" ;
            value = "" ;
            is_name = true ;
            // v_cout << "New object at " << token_ptr << ", parent: " << token_ptr->parent << "\n";
        }
        else if (c == ',' || c == '}'){
            // v_cout << "Adding to " << token_ptr << " : " << name << " : " << value << "\n";
            
            if (value != "")
                token_ptr->set_attribute(name, value);

            name = "";
            value = "";
            is_name = true;
            
            if (c == '}'){
                token_ptr = token_ptr->parent;
            }
        }
        else if (c == ':' && is_name) {
            is_name = false;
        }
        else if (c == ':' && ! is_name) {
            std::cerr << "Error in file: " << filename << "\n";
            
            break;
        }
        else if (c != '\n' && c != '\t' && c != '\"' && c != ' '){
            if (is_name) name += c;
            else value += c;
        }        
    }

    file.close();

    // v_cout << "End at object : " << token_ptr << " (" << (token_ptr==&root)<< ")\n";


    return root;
}

