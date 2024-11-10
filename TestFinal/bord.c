int f_called = 0;
int g_called = 0;

int f() {
    f_called = 1;  // Effet de bord : marquer que f a été appelée
    return 0;      // Retourne 0, donc `f()` échoue
}

int g() {
    g_called = 1;  // Effet de bord : marquer que g a été appelée
    return 1;      // Retourne 1, donc `g()` réussit
}

int main() {
    if (f() && g()) {
        print_int(1);
    } else {
        print_int(0);  // Cette branche sera exécutée car f() retourne 0
    }
    print_int(f_called);  // Doit imprimer 1, f() a été appelée
    print_int(g_called);  // Ne doit pas imprimer 1, g() n'a pas été appelée car f() échoue
    return 0;
}
