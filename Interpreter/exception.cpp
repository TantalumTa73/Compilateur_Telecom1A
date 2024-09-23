#include <exception>
#include <string>
#include "exception.hpp"

InterpretException::InterpretException(
            int start_line, int start_char,
            int end_line, int end_char, const char* msg
) : start_line(start_line), start_char(start_char), 
end_line(end_line), end_char(end_char),
message(msg) {
    error_message = 
        "Error at line " + std::to_string(start_line) + 
        ", char " + std::to_string(start_char) + 
        " to line " + std::to_string(end_line) + 
        ", char " + std::to_string(end_char) + ": " + message;
};

const char* InterpretException::what() const throw(){
    return error_message.c_str();
}