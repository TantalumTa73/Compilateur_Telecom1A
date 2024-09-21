#include "token.hpp"
#include <vector>

Token::Token(){
    name = "";
    start_line = 0;
    start_char = 0;
    end_line = 0;
    end_char = 0;
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
    childs = std::vector<Token>();
}

std::string Token::get_attribute(std::string key) {
    auto it = attributes.find(key);
    if (it != attributes.end()) {
        return it->second;
    }
    return "";
}

void Token::add_attribute(std::string key, std::string value) {
    attributes[key] = value;
    return ;
}

