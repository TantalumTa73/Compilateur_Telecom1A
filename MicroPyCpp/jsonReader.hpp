#pragma once
#include "token.hpp"


class JsonReader {
    public:
        JsonReader(std::string filename) : filename(filename) {} ;
        Root readFile();
    private:

        const std::string filename;
        vector<Token*> tokens ;

        void add_attribute(std::string name, std::string value, Token* tk);
};