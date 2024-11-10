#include <stdbool.h>

bool f() {
    print_int(0);
    return true;
}

bool g() {
    print_int(1);
    return true;
}

int main() {

    if (f() || g()) {
        print_int(0);
    } else {
        print_int(3);
    }

}