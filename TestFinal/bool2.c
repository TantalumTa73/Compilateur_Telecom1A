#include <stdbool.h>

int g(int a) {
    return 2*a;
}

int main() {

    int* a;
    int n = 100;
    n = g(n);
    print_int(n);
    
    
    a = own_malloc(sizeof(int) * n);
    

    for (int i = 0; i < n; i = i + 1) {
        a[i] = i*i;
    }

    for (int i = 0; i < n; i = i + 1) {
        print_int(a[i]);
    }
    print_int(a[0]);



}