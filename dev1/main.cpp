#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// dev1/Game.cpp
void bersihkanLayar();
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
    bersihkanLayar();

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
            bersihkanLayar();
            continue;
        }

        cin.ignore(10000, '\n');

        if (menu == 1) {
            bersihkanLayar();

            bool mainLagi = true;

            while (mainLagi) {
                int skorPemain = 0;
                int skorKomputer = 0;
                int ronde = 1;

                while (ronde <= 3) {
                    if (ronde > 1) {
                        bersihkanLayar();
                    }

                    // Halaman awal ronde
                    cout << "\n+--------------------------------------+\n";
                    cout << "|              BOCIL RPS               |\n";
                    cout << "|              ROUND " << ronde << "                 |\n";
                    cout << "|                                      |\n";
                    cout << "| SCORE                                |\n";
                    cout << "| PLAYER: " << skorPemain << "          COMPUTER: " << skorKomputer << "       |\n";
                    cout << "+--------------------------------------+\n";

                    int pemain = inputPemain();
                    int komputer = pilihanKomputer();
                    int hasil = cekHasil(pemain, komputer);

                    if (hasil == 1) {
                        skorPemain = skorPemain + 1;
                    } else if (hasil == 2) {
                        skorKomputer = skorKomputer + 1;
                    }

                    bersihkanLayar();

                    // Halaman hasil ronde
                    cout << "\n+--------------------------------------+\n";
                    cout << "|              BOCIL RPS               |\n";
                    cout << "|              ROUND " << ronde << "                 |\n";
                    cout << "|                                      |\n";
                    cout << "| SCORE                                |\n";
                    cout << "| PLAYER: " << skorPemain << "          COMPUTER: " << skorKomputer << "       |\n";
                    cout << "+--------------------------------------+\n";

                    tampilHasil(pemain, komputer, hasil);

                    cin.get();

                    ronde = ronde + 1;
                }

                bersihkanLayar();
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
                            bersihkanLayar();
                        } else if (pilihanAkhir == 2) {
                            pilihMenuAkhir = false;
                            mainLagi = false;
                            bersihkanLayar();
                        } else if (pilihanAkhir == 3) {
                            pilihMenuAkhir = false;
                            mainLagi = false;
                            programJalan = false;
                        } else {
                            cout << "\nPilihan tidak tersedia. Masukkan angka 1 sampai 3.\n";
                        }
                    }
                }
            }
        } else if (menu == 2) {
            bersihkanLayar();
            tampilAturan();
            cin.get();
            bersihkanLayar();
        } else if (menu == 3) {
            bersihkanLayar();
            tampilAbout();
            cin.get();
            bersihkanLayar();
        } else if (menu == 4) {
            programJalan = false;
        } else {
            cout << "\nMenu tidak tersedia. Pilih angka 1 sampai 4.\n";
            cout << "Tekan ENTER untuk kembali ke menu...";
            cin.get();
            bersihkanLayar();
        }
    }

    bersihkanLayar();
    cout << "\n+--------------------------------------+\n";
    cout << "|                                      |\n";
    cout << "|              BOCIL RPS               |\n";
    cout << "|                                      |\n";
    cout << "|     Terima kasih sudah bermain!      |\n";
    cout << "|                                      |\n";
    cout << "+--------------------------------------+\n";

    return 0;
}