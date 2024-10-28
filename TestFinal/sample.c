#include <stdbool.h>

int main() {

    int a = 5;
    int b = 3;

    for (int c = 0; c < 5; c = c + 1) {
        for (int j = 0; j < c; j = j + 1) {
            b = b + 10 * c + j;
            print(b);
        }
    }

    // print(b > 100);
    if (b > 100) {
        print(2*b);
    }

    if (b > 400) {
        print(3*b);
    } else {
        print(60);
    }

    if (20 > 10) {
        if (10 < 6) {
            print(1);
        } else {
            print(2);
        }
    } else {
        print(3);
    }

}