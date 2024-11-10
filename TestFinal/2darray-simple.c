int arr[2][3][3];

void init_3d_array() {
    int i;
    int j;
    int k;
    i = 0;
    while (i < 2) {
        j = 0;
        while (j < 3) {
            k = 0;
            while (k < 3) {
                *(*(*(arr + i) + j) + k) = i + j + k;
                k = k + 1;
            }
            j = j + 1;
        }
        i = i + 1;
    }
}

void print_3d_array() {
    int i;
    int j;
    int k;
    i = 0;
    while (i < 2) {
        j = 0;
        while (j < 3) {
            k = 0;
            while (k < 3) {
                print_int(arr[i][j][k]);
                k = k + 1;
            }
            j = j + 1;
        }
        i = i + 1;
    }
}

int main() {
    init_3d_array();
    print_3d_array();
    return 0;
}
