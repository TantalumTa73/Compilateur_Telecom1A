#include <exception>
#include <string>
#include "exception.hpp"

InterpreterException::InterpreterException(
            int start_line, int start_char,
            int end_line, int end_char, std::string msg
) : start_line(start_line), start_char(start_char), 
end_line(end_line), end_char(end_char),
message(msg) {
    error_message = 
        "Error at line " + std::to_string(start_line) + 
        ", char " + std::to_string(start_char) + 
        " to line " + std::to_string(end_line) + 
        ", char " + std::to_string(end_char) + ": " + message;
};

InterpreterException::InterpreterException( Token token, std::string msg ): 
start_line(token.start_line), start_char(token.start_char), 
end_line(token.end_line), end_char(token.end_char),
message(msg) {
    error_message = 
        "Error at line " + std::to_string(token.start_line) + 
        ", char " + std::to_string(token.start_char) + 
        " to line " + std::to_string(token.end_line) + 
        ", char " + std::to_string(token.end_char) + ": " + message;
};

InterpreterException::InterpreterException( TkPtr token, std::string msg ): 
start_line(token->start_line), start_char(token->start_char), 
end_line(token->end_line), end_char(token->end_char),
message(msg) {
    error_message = 
        "Error at line " + std::to_string(token->start_line) + 
        ", char " + std::to_string(token->start_char) + 
        " to line " + std::to_string(token->end_line) + 
        ", char " + std::to_string(token->end_char) + ": " + message;
};



const char* InterpreterException::what() const throw(){
    return error_message.c_str();
}