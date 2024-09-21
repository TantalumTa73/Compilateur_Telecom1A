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
        std::vector<Token> childs ;

        Token() ;
        Token(std::string name, int start_line, int start_char, int end_line, int end_char) ;

        void add_attribute(std::string key, std::string value) ;
        std::string get_attribute(std::string key) ;

    private:
        std::unordered_map<std::string, std::string> attributes ;
};

// class gvardef : Token {} ;
// class gfundef : Token {} ;
// class varset : Token {} ;
