#include <iostream>
#include <string>
#include <vector>

using namespace std;

string vigenereCipher(string text, string key, bool encrypt) {
    string result = "";
    int textLen = text.length();
    int keyLen = key.length();

    for (int i = 0; i < textLen; i++) {
        char textChar = text[i];
        char keyChar = key[i % keyLen];
        int shift = encrypt ? (keyChar - 'A') : -(keyChar - 'A');
        char transformedChar = ((textChar - 'A' + shift + 26) % 26) + 'A';

        result += transformedChar;
    }

    return result;
}

void displayMenu() {
    cout << "Menu Vigenere Cipher:\n";
    cout << "1. Enkripsi\n";
    cout << "2. Dekripsi\n";
    cout << "Masukkan pilihan: ";
}

int main() {
    char choice;
    string key, inputText, result;

    while (true) {
        displayMenu();
        cin >> choice;

        if (choice == '1') {
            cout << "Masukkan plaintext (Masukkan dengan huruf kapital): ";
            cin.ignore();
            getline(cin, inputText);

            cout << "Masukkan key (Masukkan dengan huruf kapital): ";
            getline(cin, key);

            result = vigenereCipher(inputText, key, true);
            cout << "Hasil Enkripsi: " << result << endl;
        }
        
        else if (choice == '2') {
            cout << "Masukkan ciphertext (Masukkan dengan huruf kapital): ";
            cin.ignore();
            getline(cin, inputText);

            cout << "Masukkan key (Masukkan dengan huruf kapital): ";
            getline(cin, key);

            result = vigenereCipher(inputText, key, false);
            cout << "Hasil Dekripsi: " << result << endl;
        }
        
        else {
            cout << "Salah. Diulang kembali.\n";
        }

        cout << "Lanjut? (y/n): ";
        cin >> choice;
        if (choice != 'y' && choice != 'Y')
            break;
    }

    return 0;
}
