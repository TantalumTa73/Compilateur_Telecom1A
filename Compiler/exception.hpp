#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

#include "token.hpp"

class InterpreterException : public std::exception {
    private:
        std::string message;
        std::string error_message;
        int start_line ;
        int start_char ;
        int end_line ;
        int end_char ;

    public:
        InterpreterException(
            int start_line, int start_char,
            int end_line, int end_char,
            std::string msg
        ) ;
        InterpreterException( Token token, std::string msg ) ;

        const char* what() const throw();
};
#endif