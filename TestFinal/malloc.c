int main(){
    int *a = malloc(sizeof(int) * 2);
    a[1] = 42;
    print_int(a[1]);
    return 0;
}