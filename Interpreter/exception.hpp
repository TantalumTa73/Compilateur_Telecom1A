#include <exception>
#include <string>

class InterpretException : public std::exception {
    private:
        std::string message;
        std::string error_message;
        int start_line ;
        int start_char ;
        int end_line ;
        int end_char ;

    public:
        InterpretException(
            int start_line, int start_char,
            int end_line, int end_char, const char* msg
        ) ;

        const char* what() const throw();
};