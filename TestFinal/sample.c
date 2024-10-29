#include <stdbool.h>

int factorial(int n, bool a) {
    if (n == 0) {
        if (a) {
            return 1;
        }
        return 2;
    } else {
        return n * factorial(n - 1, a);
    }
}


int main() {
    int a[6];
    a[0] = 1;
}