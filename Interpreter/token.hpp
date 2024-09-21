#pragma once
#include <vector>
#include <string>
#include <unordered_map>

// enum class Type {
//     NUMBER,
//     STRING,
//     IDENTIFIER,
//     OPERATOR,
//     KEYWORD,
//     PUNCTUATION,
//     END
// };

class Token {
    public:
        std::string name ;
        int start_line ;
        int start_char ;
        int end_line ;
        int end_char ;
        Token* parent ;

        std::vector<Token> childs ;
        std::unordered_map<std::string, std::string> attributes ;

        Token();
        Token(std::string name, int start_line, int start_char, int end_line, int end_char) ;

        std::string get_attribute(std::string key) ;
        void set_attribute(std::string key, std::string value) ;
        
        void add_child(Token child) ;

        void print();
        void print(std::string indent);

    // private:
};

// class gvardef : Token {} ;
// class gfundef : Token {} ;
// class varset : Token {} ;
