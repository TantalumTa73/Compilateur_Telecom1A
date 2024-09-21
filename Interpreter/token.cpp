#include <vector>
#include <iostream>
#include "token.hpp"

Token::Token(){
    name = "";
    start_line = 0;
    start_char = 0;
    end_line = 0;
    end_char = 0;
    parent = nullptr;
    childs = std::vector<Token>();
}

Token::Token(
    std::string name_, int start_line_, int start_char_,
    int end_line_, int end_char_ 
){
    name = name_;
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
    attributes[key] = value;
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
    std::cout << indent << "Name: " << name << "\n";
    std::cout << indent << "Start Line: " << start_line << "\n";
    std::cout << indent << "Start Char: " << start_char << "\n";
    std::cout << indent << "End Line: " << end_line << "\n";
    std::cout << indent << "End Char: " << end_char << "\n";
    if (attributes.size() != 0){
        std::cout << indent << "Attributes: \n";
        for (auto a : attributes){
            std::cout << indent << "\t" << a.first << " : " << a.second << "\n";
        }
    }
    if (childs.size() != 0){
        std::cout << indent << "Childs: \n";
        for (Token t : childs){
            t.print(indent + "\t");
        }
    }
    return ;
}

