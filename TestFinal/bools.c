#include <stdbool.h>

int main() {
    print_int(!false);

    print_int((true || true) && false);

}