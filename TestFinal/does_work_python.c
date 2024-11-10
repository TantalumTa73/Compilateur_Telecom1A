#include <stdbool.h>

bool f() {
    print_int(0);
    return false;
}

bool g() {
    print_int(1);
    return false;
}

int main() {

    if (f() && g()) {
        print_int(0);
    } else {
        print_int(3);
    }

}