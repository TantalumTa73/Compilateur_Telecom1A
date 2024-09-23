#include <exception>
#include <string>

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
            // const char* msg
            std::string msg
        ) ;

        const char* what() const throw();
};