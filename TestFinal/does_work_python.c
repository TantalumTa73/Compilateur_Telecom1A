#include <stdbool.h>

int t[1000];

int somme(int a, int b, int c, int d, int e) {
    return a + b + c + d + e;
}

int factorielle(int n) {
    if (n <= 1) {
        return 1;
    }
    return factorielle(n - 1) * n;
}

int main() {

    int f7 = factorielle(7);

    int f7_iter = 1;
    for (int i = 1; i <= 7; i = i + 1) {
        f7_iter = f7_iter * i;
    }

    if (f7 == f7_iter) {
        print_int(0);
    } else {
        print_int(1);
    }

    while (true) {
        
        print_int(f7);
        if (f7 > 5045) {
            break;
        } else {
            f7 = f7 + 1;
        }

        while (false) {

        }

        continue;
        break;

    }

    int n = 1000;
    for (int i = 0; i < n; i = i + 1) {
        t[i] = i;
    }

    int s = 0;
    for (int i = 0; i < n; i = i + 1) {
        s = s + t[i];
    }

    print_int(s);

    int d = n * (n - 1) / 2;
    print_int(d);

    if (!(d != s)) {
        print_int(0);
    }

}