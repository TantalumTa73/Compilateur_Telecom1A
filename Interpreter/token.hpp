#include <vector>
#include <string>

enum class Type {
    NUMBER,
    STRING,
    IDENTIFIER,
    OPERATOR,
    KEYWORD,
    PUNCTUATION,
    END
};

class Token {
    public:

        std::string action ;
        std::string name ;
        int start_line ;
        int start_char ;
        int end_line ;
        int end_char ;
        

        // Token(Type type, std::string value) : type(type), value(value) {}

        // Type type;
        // std::string value;
};

class gvardef : Token {} ;
class gfundef : Token {} ;
class varset : Token {} ;

// type "action": "gvardef",
// string "name": "x",
// int "start_line": 1,
// int "start_char": 0,
// int "end_line": 1,
// int "end_char": 7

// type "action": "gfundef",
// string "name": "main",
// string "arg": "a",
// vector<> "body": []

// type "action": "varset",
// string "name": "u",
// "expr": {
//     "type": "cst",
//     "value": 42,
//     "start_line": 5,
//     "start_char": 6,
//     "end_line": 5,
//     "end_char": 8
// },
// int "start_line": 5,
// int "start_char": 2,
// int "end_line": 5,
// int "end_char": 10