
int a[100][100];



int main() {

    int n = 10;

    a[1][1] = 1;
    for (int i = 1; i < n; i = i + 1) {
        a[i][1] = 1;
        a[i][i] = 1;
        for (int j = 2; j < i; j = j + 1) {
            a[i][j] = a[i - 1][j] + a[i - 1][j - 1];
        }
    }    

    for (int i = 1; i < n; i = i + 1) {
        for (int j = 1; j <= i; j = j + 1) {
            print_int(a[i][j]);
        }
    }
    
}