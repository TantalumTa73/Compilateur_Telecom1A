int tab[100];

int main(){
    for (int i = 0; i < 100; i = i + 1){
        tab[i] = i;
    }
    for (int i = 0; i < 100; i = i + 1){
        print_int(tab[i]);
    }
    return 0;
}