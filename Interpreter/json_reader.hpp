#pragma once
#include "token.hpp"


class JsonReader {
    public:
        JsonReader(std::string filename) : filename(filename) {} ;
        Token readFile();
    private:
        const std::string filename;
};