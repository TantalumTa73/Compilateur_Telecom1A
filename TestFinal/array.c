int main(){
        int t[3][3];
        *(t[1] + 2) = 42;
        print_int(t[1][2]);
    return 0;
}