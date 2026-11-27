#include <iostream>

using namespace std;

int inputPemain() {
    int pilihan = 0;
    bool valid = false;

    while (!valid) {
        cout << "\n+--------------------------------------+\n";
        cout << "|            PILIHAN PEMAIN            |\n";
        cout << "|                                      |\n";
        cout << "|  1. BATU                             |\n";
        cout << "|  2. GUNTING                          |\n";
        cout << "|  3. KERTAS                           |\n";
        cout << "|                                      |\n";
        cout << "+--------------------------------------+\n";
        cout << "Pilih (1-3): ";

        if (cin >> pilihan) {
            cin.ignore(10000, '\n');

            if (pilihan >= 1 && pilihan <= 3) {
                valid = true;
            } else {
                cout << "Pilihan tidak tersedia! Masukkan angka 1 sampai 3.\n";
            }
        } else {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Input harus berupa angka! Masukkan angka 1 sampai 3.\n";
        }
    }

    return pilihan;
}