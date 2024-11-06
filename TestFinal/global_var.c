int a;

int f() {
    print_int(a);
}

int main() {
    int c;
    a = 5;
    print_int(a);
    int a = 2;
    print_int(a);
    f();
}