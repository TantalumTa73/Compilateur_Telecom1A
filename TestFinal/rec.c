#include <stdbool.h>

int factorial(int n, int a) {
    
    if (n <= 0) {
        return a ;
    } else {
        return n*factorial(n-1, a);
    }
}


int main() {
    int x = factorial(10, 2) ;
    print_int(x);
}