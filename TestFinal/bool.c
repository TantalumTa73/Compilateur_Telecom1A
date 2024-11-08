bool a = true;
bool b = false;

int c;
int d = 5;

int main() {

    a = true;
    b = false;

    c = 3;
    d = 5;
    
    print_int(c);

    if (c) {
        print_int(3);
    } else {
        print_int(4);
    }

    print_int(a);
    print_int(b);
    print_int(c && d);
}