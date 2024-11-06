int main() {
    int b;
    b = 1;
    print_int(b);
    int* a;
    a = &b;
    // int c;
    // c = *a;
    print_int(*a);

    int* c2 = &a;
    int* c3 = &c2;
    // int*** c3 = &c2;
    // int**** c4 = &c3;
    // int***** c5 = &c5;
    print_int(***c3);
}