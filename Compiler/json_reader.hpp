#ifndef JSON_READER_H
#define JSON_READER_H

#include <fstream>

#include "token.hpp"

class JsonReader {
    public:
        JsonReader(std::string filename) : filename(filename) {} ;
        Token* readFile();
    private:
        const std::string filename;
        Token* to_token(RawToken raw_token);
};
#endif