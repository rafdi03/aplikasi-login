#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <cstdlib>
#include <cctype> // Library untuk validasi huruf dan angka

using namespace std;

// Struktur data untuk menyimpan informasi pengguna
struct User {
    string username;
    string password;
    int points;
};

// Struktur data untuk menyimpan poin dalam billboard
struct Score {
    string username;
    int points;
};

// Fungsi untuk mencari pengguna berdasarkan nama pengguna
int findUser(const vector<User>& users, const string& username) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i].username == username) {
            return i; // Pengguna ditemukan, mengembalikan indeksnya
        }
    }
    return -1; // Pengguna tidak ditemukan
}

// Fungsi untuk memainkan permainan tebak angka
int playGame() {
    int randomNumber = rand() % 50 + 1; // Angka acak antara 1 dan 50
    int guess;
    int attempts = 0;

    cout << "=== Selamat datang di Tebak Angka! ===" << endl;
    cout << "Saya sudah memilih angka antara 1 dan 50. Cobalah menebaknya." << endl;

    while (true) {
        cout << "Tebak angka: ";
        cin >> guess;
        attempts++;

        if (guess < randomNumber) {
            cout << "Tebakan terlalu rendah. Coba lagi." << endl;
        } else if (guess > randomNumber) {
            cout << "Tebakan terlalu tinggi. Coba lagi." << endl;
        } else {
            cout << "Selamat! Anda menebak angka dengan benar dalam " << attempts << " percobaan." << endl;
            return attempts;
        }
    }
}

// Fungsi untuk memeriksa apakah string hanya mengandung huruf dan angka
bool isAlphaNumeric(const string& str) {
    for (char c : str) {
        if (!isalnum(c)) {
            return false;
        }
    }
    return true;
}

int main() {
    vector<User> users; // Vector untuk menyimpan pengguna yang terdaftar
    vector<Score> billboard; // Vector untuk menyimpan poin dalam billboard
    bool isLoggedIn = false; // Status login
    string currentUsername; // Untuk menyimpan nama pengguna yang sedang login

    while (true) {
        cout << "============================================" << endl;
        if (isLoggedIn) {
            cout << "Selamat datang, " << currentUsername << "!" << endl;
            cout << "Poin Anda: " << users[findUser(users, currentUsername)].points << endl;
            cout << "============================================" << endl;
            cout << "1. Bermain Tebak Angka" << endl;
            cout << "2. Billboard" << endl;
            cout << "3. Logout" << endl;
        } else {
            cout << "1. Login" << endl;
            cout << "2. Register" << endl;
        }
        cout << "4. Exit dari Program" << endl;
        cout << "============================================" << endl;
        cout << "Pilihan: ";

        int choice;
        cin >> choice;

        // Membersihkan layar konsol
        system("cls");

        if (isLoggedIn) {
            if (choice == 1) { // Bermain Tebak Angka
                int attempts = playGame(); // Bermain tebak angka
                for (User& user : users) {
                    if (user.username == currentUsername) {
                        user.points += (10 - attempts); // Menambah poin
                        billboard.push_back({user.username, user.points}); // Menyimpan ke billboard
                    }
                }
            } else if (choice == 2) { // Billboard
                cout << "=== Billboard ===" << endl;
                cout << "Nama\t\tPoin\t\tJuara" << endl;

                // Mengurutkan billboard berdasarkan poin secara menurun
                sort(billboard.begin(), billboard.end(), [](const Score& a, const Score& b) {
                    return a.points > b.points;
                });

                int numToShow = min(3, static_cast<int>(billboard.size())); // Jumlah pemain yang akan ditampilkan

                for (int i = 0; i < numToShow; i++) {
                    cout << billboard[i].username << "\t\t" << billboard[i].points << "\t\tJuara " << (i + 1) << endl;
                }
            } else if (choice == 3) { // Logout
                isLoggedIn = false;
                currentUsername = "";
            }
        }

        if (!isLoggedIn) {
            if (choice == 1) { // Login
                string username, password;
                cout << "=== Login ===" << endl;
                cout << "Masukkan nama pengguna: ";
                cin >> username;

                int userIndex = findUser(users, username);
                if (userIndex != -1) {
                    cout << "Masukkan kata sandi: ";
                    cin >> password;

                    if (users[userIndex].password == password) {
                        isLoggedIn = true;
                        currentUsername = username;
                        cout << "Login berhasil! Selamat datang, " << username << "!" << endl;
                    } else {
                        cout << "Maaf, kata sandi Anda salah." << endl;
                    }
                } else {
                    cout << "Maaf, nama pengguna tidak ditemukan." << endl;
                }
            } else if (choice == 2) { // Register
                string username, password;
                cout << "=== Register ===" << endl;
                cout << "Masukkan nama pengguna baru: ";
                cin >> username;

                if (!isAlphaNumeric(username)) {
                    cout << "Nama pengguna hanya boleh mengandung huruf dan angka." << endl;
                    continue;
                }

                int userIndex = findUser(users, username);
                if (userIndex != -1) {
                    cout << "Nama pengguna sudah terdaftar. Silakan pilih nama pengguna lain." << endl;
                } else {
                    cout << "Masukkan kata sandi baru: ";
                    cin >> password;
                    users.push_back({username, password, 0}); // Inisialisasi poin awal dengan 0
                    cout << "Registrasi berhasil! Selamat datang, " << username << "!" << endl;
                }
            } else if (choice == 4) { // Exit dari Program
                cout << "Terima kasih telah mencoba. Sampai jumpa!" << endl;
                break; // Keluar dari program
            }
        }
    }

    return 0;
}
