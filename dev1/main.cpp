#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// dev1/Game.cpp
void tampilMenu();
void tampilAturan();
void tampilAbout();
void tampilHasil(int pemain, int komputer, int hasil);
void tampilHasilAkhir(int skorPemain, int skorKomputer);

// dev2/Player.cpp
int inputPemain();

// dev3/Computer.cpp
int pilihanKomputer();
string namaPilihan(int pilihan);
int cekHasil(int pemain, int komputer);

int main() {
    srand(time(0));

    bool programJalan = true;

    while (programJalan) {
        tampilMenu();

        int menu;
        cout << "Pilih menu (1-4): ";

        if (!(cin >> menu)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInput menu harus berupa angka!\n";
            cout << "Tekan ENTER untuk kembali ke menu...";
            cin.get();
            continue;
        }

        cin.ignore(10000, '\n');

        if (menu == 1) {
            bool mainLagi = true;

            while (mainLagi) {
                int skorPemain = 0;
                int skorKomputer = 0;
                int ronde = 1;

                while (ronde <= 3) {
                    cout << "\n+--------------------------------------+\n";
                    cout << "|              BOCIL RPS               |\n";
                    cout << "|                                      |\n";
                    cout << "|              ROUND " << ronde << "                 |\n";
                    cout << "|                                      |\n";
                    cout << "| SCORE                                |\n";
                    cout << "| PLAYER: " << skorPemain << "          COMPUTER: " << skorKomputer << "       |\n";
                    cout << "+--------------------------------------+\n";

                    int pemain = inputPemain();
                    int komputer = pilihanKomputer();
                    int hasil = cekHasil(pemain, komputer);

                    tampilHasil(pemain, komputer, hasil);

                    if (hasil == 1) {
                        skorPemain = skorPemain + 1;
                    } else if (hasil == 2) {
                        skorKomputer = skorKomputer + 1;
                    }

                    cout << "\nSCORE SEMENTARA\n";
                    cout << "PLAYER: " << skorPemain << "          COMPUTER: " << skorKomputer << "\n";

                    ronde = ronde + 1;

                    cout << "\nTekan ENTER untuk melanjutkan...";
                    cin.get();
                }

                tampilHasilAkhir(skorPemain, skorKomputer);

                bool pilihMenuAkhir = true;

                while (pilihMenuAkhir) {
                    int pilihanAkhir;
                    cout << "Pilih menu (1-3): ";

                    if (!(cin >> pilihanAkhir)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "\nInput harus berupa angka 1 sampai 3!\n";
                    } else {
                        cin.ignore(10000, '\n');

                        if (pilihanAkhir == 1) {
                            pilihMenuAkhir = false;
                        } else if (pilihanAkhir == 2) {
                            pilihMenuAkhir = false;
                            mainLagi = false;
                        } else if (pilihanAkhir == 3) {
                            pilihMenuAkhir = false;
                            mainLagi = false;
                            programJalan = false;
                            cout << "\nTerima kasih sudah bermain BOCIL RPS!\n";
                        } else {
                            cout << "\nPilihan tidak tersedia. Masukkan angka 1 sampai 3.\n";
                        }
                    }
                }
            }
        } else if (menu == 2) {
            tampilAturan();
            cout << "\nTekan ENTER untuk kembali ke menu utama...";
            cin.get();
        } else if (menu == 3) {
            tampilAbout();
            cout << "\nTekan ENTER untuk kembali ke menu utama...";
            cin.get();
        } else if (menu == 4) {
            cout << "\nTerima kasih sudah bermain BOCIL RPS!\n";
            programJalan = false;
        } else {
            cout << "\nMenu tidak tersedia. Pilih angka 1 sampai 4.\n";
            cout << "Tekan ENTER untuk kembali ke menu...";
            cin.get();
        }
    }

    return 0;
}