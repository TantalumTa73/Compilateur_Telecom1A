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

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int main() {

    int a = -5;
    print_int(a);
    print_int(3 + 5 / 5 + 3 * (3 + 1));
    print_int(5 ^ 3);

    int f7 = factorielle(7);
    print_int(somme(1, 2, 3, 4, 5));

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

    print_int(1000000007);

    int a = 3;
    int b = 17;
    swap(&a, &b);
    print_int(a);
    print_int(b);

    print_int(1000000007);

    int r[10][13][29];
    for (int i = 0; i < 10; i = i + 1) {
        for (int j = 0; j < 13; j = j + 1) {
            for (int k = 0; k < 29; k = k + 1) {

                r[i][j][k] = i + j + k;
                *(*(*(r + i) + j) + k) = *(*(*(r + i) + j) + k) + 7;

                if (((i + j + k) % 19) == 0 && i > 8 && j > 10) {
                    print_int(r[i][j][k]);
                }

            }
        }
    }

    print_int(1000000007);

    int* q = malloc(sizeof(int) * 1000);
    int t = 0;
    
    for (int i = 0; i < 1000; i = i + 1) {
        q[i] = i;
        t = t + q[i];
    }

    print_int(t);

}