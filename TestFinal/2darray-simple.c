int main() {

    int t[10][10];
    int** a;
    int* b;
    for (int i = 0; i < 10; i = i + 1) {
        for (int j = 0; j < 10; j = j + 1) {
            t[i][j] = i * j;
        }
    }

    // t[2][0] = 3;

    a = &t[2];
    int* v = (&a[3][2]);
    print_int(v[1]);

    print_int(a[0][3]);

}