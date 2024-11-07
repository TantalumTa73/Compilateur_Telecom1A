int main() {

    int i = 0;
    while (i < 10) {
        print_int(i);
        i = i + 1;
    }

    i = 0;
    while (i < 10) {
        i = i + 1;
        if (i % 2 == 0) {
            continue;
        }
        print_int(i);
    }

    i = 0;
    while (i < 10) {
        if (i == 2) {
            break;
        }
        print_int(i);
        i = i + 1;
    }

    print_int(i);

}