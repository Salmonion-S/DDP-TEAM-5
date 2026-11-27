#include <cstdlib>
#include <string>

using namespace std;

int pilihanKomputer() {
    return rand() % 3 + 1;
}

string namaPilihan(int pilihan) {
    if (pilihan == 1) {
        return "BATU";
    } else if (pilihan == 2) {
        return "GUNTING";
    } else if (pilihan == 3) {
        return "KERTAS";
    } else {
        return "TIDAK DIKETAHUI";
    }
}

int cekHasil(int pemain, int komputer) {
    if (pemain == komputer) {
        return 0;
    } else if ((pemain == 1 && komputer == 2) ||
               (pemain == 2 && komputer == 3) ||
               (pemain == 3 && komputer == 1)) {
        return 1;
    } else {
        return 2;
    }
}