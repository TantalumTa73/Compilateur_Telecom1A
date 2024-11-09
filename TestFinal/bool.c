#include <stdbool.h>

bool a = true;
bool b = false;
bool c = 2;
bool d = 4;

int main() {

    a = true;
    b = false;

    c = 2;
    d = 4;
    
    print_int(c);

    if (c) {
        print_int(3);
    } else {
        print_int(4);
    }

    // print_int(a);
    // print_int(b);
    // print_int(c && d);
    print_int( true && (1 - 1));
    // print_int((1 + 3) && (1 + 1));
}