int tab[3][3][3];

int main(){
    int b = 0;
    for (int i = 0; i < 3; i ++){
        for (int j = 0; j < 3; j ++){
            for (int k = 0; k < 3; k ++){
                tab[i][j][k] = b;
                b ++;
            }
        }
    }

    for (int i = 0; i < 3; i ++){
        for (int j = 0; j < 3; j ++){
            for (int k = 0; k < 3; k ++){
                print_int(tab[i][j][k]);
            }
        }
    }
    return 0;
}