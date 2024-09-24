#include <vector>
#include <iostream>
#include "token.hpp"

bool verbose = false;

Token::Token(){
    start_line = 0;
    start_char = 0;
    end_line = 0;
    end_char = 0;
    parent = nullptr;
    childs = std::vector<Token>();
}

Token::Token(
    int start_line_, int start_char_,
    int end_line_, int end_char_ 
){
    start_line = start_line_;
    start_char = start_char_;
    end_line = end_line_;
    end_char = end_char_;
    parent = nullptr;
    childs = std::vector<Token>();
}

std::string Token::get_attribute(std::string key) {
    auto it = attributes.find(key);
    if (it != attributes.end()) {
        return it->second;
    }
    return "";
}

void Token::set_attribute(std::string key, std::string value) {
    if      (key == "start_line") start_line = std::stoi(value);
    else if (key == "start_char") start_char = std::stoi(value);
    else if (key == "end_line") end_line = std::stoi(value);
    else if (key == "end_char") end_char = std::stoi(value);
    else attributes[key] = value;
    
    return ;
}

void Token::add_child(Token child){
    child.parent = this;
    childs.push_back(child);
    return ;
}

void Token::print(){
    Token::print("");
    return ;
}
void Token::print(std::string indent = ""){

    
    v_cout << indent << "Start Line: " << start_line << "\n";
    v_cout << indent << "Start Char: " << start_char << "\n";
    v_cout << indent << "End Line: " << end_line << "\n";
    v_cout << indent << "End Char: " << end_char << "\n";
    if (attributes.size() != 0){
        v_cout << indent << "Attributes: \n";
        for (auto a : attributes){
            v_cout << indent << "\t" << a.first << " : " << a.second << "\n";
        }
    }
    if (childs.size() != 0){
        v_cout << indent << "Childs: \n";
        for (Token t : childs){
            t.print(indent + "\t");
        }
    }
    return ;
}

