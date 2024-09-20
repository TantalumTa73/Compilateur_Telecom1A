#include "token.hpp"


class JsonReader {
    public:
        JsonReader(std::string filename) : filename(filename) {}
        void read();
        std::vector<Token> get_tokens() { return tokens; }
    private:
        std::string filename;
        std::vector<Token> tokens;
};