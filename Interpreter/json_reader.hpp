#pragma once
#include "token.hpp"


class JsonReader {
    public:
        JsonReader(std::string filename) : filename(filename) {} ;
        void readFile();
        std::vector<Token> get_tokens() { return tokens; } ;
    private:
        const std::string filename;
        std::vector<Token> tokens;
};