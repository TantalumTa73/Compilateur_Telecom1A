int arr[6][6];

void init_alternating_pattern() {
    int i;
    int j;
    i = 0;
    while (i < 6) {
        j = 0;
        while (j < 6) {
            arr[i][j] = (i + j) % 2;
            j = j + 1;
        }
        i = i + 1;
    }
}

void print_alternating_pattern() {
    int i;
    int j;
    i = 0;
    while (i < 6) {
        j = 0;
        while (j < 6) {
            print_int(arr[i][j]);
            j = j + 1;
        }
        i = i + 1;
    }
}

int main() {
    init_alternating_pattern();
    print_alternating_pattern();
    return 0;
}
