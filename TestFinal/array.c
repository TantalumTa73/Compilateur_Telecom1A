int tab[2][3];

int main(){
    *(tab[1] + 2) = 42;
    print_int(tab[1][2]);
    return 0;
}