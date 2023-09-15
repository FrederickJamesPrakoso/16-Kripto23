#include <iostream>
#include <string>

using namespace std;

int main() {
  string alphabet = "abcdefghijklmnopqrstuvwxyz";
  string plaintext;
  cout << "Masukkan Kalimat dalam plain text: ";
  cin >> plaintext;

  int shift;
  cout << "Masukkan K dalam range (1-25): ";
  cin >> shift;

  string ciphertext;
  for (int i = 0; i < plaintext.length(); i++) {
    int index = alphabet.find(plaintext[i]);
    int newIndex = (index + shift) % alphabet.length();
    char newCharacter = alphabet[newIndex];
    ciphertext += newCharacter;
  }

  cout << "CipherText: " << ciphertext << endl;

  return 0;
}
