#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#define v_cout if (verbose) std::cout
#define nv_cout if (!verbose) std::cout

extern bool verbose ;

class Token {
    public:
        int start_line ;
        int start_char ;
        int end_line ;
        int end_char ;
        int unpushed_children;
        Token* parent ;

        std::vector<Token> children ;
        std::unordered_map<std::string, std::string> attributes ;

        Token();
        Token(int start_line, int start_char, int end_line, int end_char) ;

        std::string get_attribute(std::string key) ;
        void set_attribute(std::string key, std::string value) ;
        
        void add_child(Token child) ;

        void print();
        void print(std::string indent);

        bool isEqualTo(Token token);
};
