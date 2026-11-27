#include <iostream>
#include <string>

using namespace std;

void bersihkanLayar() {
    cout << "\033[2J\033[H";
}

string namaPilihan(int pilihan);

void tampilMenu() {
    cout << "\n+--------------------------------------+\n";
    cout << "|                                      |\n";
    cout << "|              BOCIL RPS               |\n";
    cout << "|       ROCK PAPER SCISSORS GAME       |\n";
    cout << "|                                      |\n";
    cout << "|            1. START GAME             |\n";
    cout << "|            2. HOW TO PLAY            |\n";
    cout << "|               3. ABOUT               |\n";
    cout << "|               4. EXIT                |\n";
    cout << "|                                      |\n";
    cout << "|           PILIH MENU (1-4)           |\n";
    cout << "|                                      |\n";
    cout << "+--------------------------------------+\n";
}

void tampilAturan() {
    cout << "\n+--------------------------------------+\n";
    cout << "|              HOW TO PLAY             |\n";
    cout << "|                                      |\n";
    cout << "|  1. Batu mengalahkan Gunting         |\n";
    cout << "|  2. Gunting mengalahkan Kertas       |\n";
    cout << "|  3. Kertas mengalahkan Batu          |\n";
    cout << "|                                      |\n";
    cout << "|  1 = BATU                            |\n";
    cout << "|  2 = GUNTING                         |\n";
    cout << "|  3 = KERTAS                          |\n";
    cout << "|                                      |\n";
    cout << "|  Pemain melawan komputer.            |\n";
    cout << "|  Pemain dengan skor tertinggi        |\n";
    cout << "|  setelah 3 ronde menjadi pemenang.   |\n";
    cout << "|                                      |\n";
    cout << "|      Tekan ENTER untuk kembali.      |\n";
    cout << "+--------------------------------------+\n";
}

void tampilAbout() {
    cout << "\n+--------------------------------------+\n";
    cout << "|                ABOUT                 |\n";
    cout << "|                                      |\n";
    cout << "|  BOCIL RPS adalah game Batu          |\n";
    cout << "|  Gunting Kertas melawan komputer.    |\n";
    cout << "|                                      |\n";
    cout << "|  Dibuat untuk tugas Dasar-Dasar      |\n";
    cout << "|  Pemrograman menggunakan C++17.      |\n";
    cout << "|                                      |\n";
    cout << "|  Developer:                          |\n";
    cout << "|  - Dev 1: Game Controller            |\n";
    cout << "|  - Dev 2: Player Module              |\n";
    cout << "|  - Dev 3: Computer & Result Module   |\n";
    cout << "|                                      |\n";
    cout << "|      Tekan ENTER untuk kembali.      |\n";
    cout << "+--------------------------------------+\n";
}

void tampilHasil(int pemain, int komputer, int hasil) {
    string pilihanPemain = namaPilihan(pemain);
    string pilihanKomputer = namaPilihan(komputer);

    cout << "\n+--------------------------------------+\n";
    cout << "|              HASIL RONDE             |\n";
    cout << "|                                      |\n";
    cout << "|  PLAYER             COMPUTER         |\n";
    cout << "|  " << pilihanPemain;

    for (int i = 0; i < 19 - (int)pilihanPemain.length(); i++) {
        cout << " ";
    }

    cout << pilihanKomputer;

    for (int i = 0; i < 17 - (int)pilihanKomputer.length(); i++) {
        cout << " ";
    }

    cout << "|\n";
    cout << "|                                      |\n";

    if (hasil == 1) {
        cout << "|               YOU WIN!               |\n";
    } else if (hasil == 2) {
        cout << "|            COMPUTER WINS!            |\n";
    } else {
        cout << "|                DRAW!                 |\n";
    }

    cout << "|                                      |\n";
    cout << "|   Tekan ENTER untuk melanjutkan...   |\n";
    cout << "+--------------------------------------+\n";
}

void tampilHasilAkhir(int skorPemain, int skorKomputer) {
    cout << "\n+--------------------------------------+\n";
    cout << "|                                      |\n";

    if (skorPemain > skorKomputer) {
        cout << "|               YOU WIN!               |\n";
        cout << "|                                      |\n";
        cout << "|           CONGRATULATIONS!           |\n";
    } else if (skorKomputer > skorPemain) {
        cout << "|            COMPUTER WINS!            |\n";
        cout << "|                                      |\n";
        cout << "|         TRY AGAIN NEXT TIME!         |\n";
    } else {
        cout << "|              MATCH DRAW              |\n";
        cout << "|                                      |\n";
        cout << "|             GOOD MATCH!              |\n";
    }

    cout << "|                                      |\n";
    cout << "|          PLAYER: " << skorPemain << "                   |\n";
    cout << "|          COMPUTER: " << skorKomputer << "                 |\n";
    cout << "|                                      |\n";
    cout << "|          1. PLAY AGAIN               |\n";
    cout << "|          2. MAIN MENU                |\n";
    cout << "|          3. EXIT                     |\n";
    cout << "|                                      |\n";
    cout << "+--------------------------------------+\n";
}