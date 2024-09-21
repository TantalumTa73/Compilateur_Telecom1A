#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>
#include "json_reader.hpp"
#include "token.hpp"

using Attribute = std::tuple<std::string,std::string>;
using Object = std::vector<Attribute>;


void token_from_obj(Token *token, Object obj){
    // Token token = Token();
    for (Attribute a : obj){
        std::string key = std::get<0>(a);
        std::string val = std::get<1>(a);
        if (key == "name") token->name = val;
        else if (key == "start_line") token->start_line = std::stoi(val);
        else if (key == "start_char") token->start_char = std::stoi(val);
        else if (key == "end_line") token->end_line = std::stoi(val);
        else if (key == "end_char") token->end_char = std::stoi(val);
        else token->set_attribute(key, val);
    }
    return ;
}


Token JsonReader::readFile(){

    std::ifstream file = std::ifstream(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << "\n";
        return Token();
    }

    Token root = Token("__root__", 0, 0, 0, 0);
    Token *token_ptr = &root;

    std::cout << "Main at " << token_ptr << "\n";
    
    std::vector<Attribute> obj = std::vector<Attribute>();
    std::string name ;
    std::string value ;
    bool is_name ;
    char c ;

    while ( ! file.eof() ) {
        c = file.get();
        
        if (c == '{'){
            obj = std::vector<Attribute>();
            token_ptr->add_child(Token());
            token_ptr = &token_ptr->childs.back();
            name = "";
            value = "";
            is_name = true;
            std::cout << "New object at " << token_ptr << ", parent: " << token_ptr->parent << "\n";
        }
        else if (c == ',' || c == '}'){
            Attribute a = std::make_tuple(name, value);
            // std::cout << "Adding to " << token_ptr << " : " << name << " : " << value << "\n";
            obj.push_back(a);

            name = "";
            value = "";
            is_name = true;
            
            if (c == '}'){
                token_from_obj(token_ptr, obj);
                token_ptr = token_ptr->parent;
            }
        }
        else if (c == ':' && is_name) {
            is_name = false;
        }
        else if (c == ':' && ! is_name) {
            std::cerr << "Error in file: " << filename << "\n";
            token_ptr = token_ptr->parent;
            token_from_obj(token_ptr, obj);
            break;
        }
        else if (c != '\n' && c != '\t' && c != '\"' && c != ' '){
            if (is_name) name += c;
            else value += c;
        }        
    }

    file.close();

    std::cout << "End at object : " << token_ptr << " (" << (token_ptr==&root)<< ")\n";


    std::cout << "\nPrinting objects\n";
    for (Token t : root.childs){
        t.print();
    }


    return root;
}

