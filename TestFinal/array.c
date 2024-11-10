int tab[2][2];

int main(){
    for (int i = 0; i < 2; i ++){
        for (int j = 0; j < 2; j ++){
            tab[i][j] = i * 2 + j;
        }
    }
    for (int i = 0; i < 2; i ++){
        for (int j = 0; j < 2; j ++){
            print_int(tab[i][j]);
        }
    }
    return 0;
}