#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int MATRIX_SIZE = 3;

bool getMatrixInverse(const std::vector<std::vector<int>>& matrix, std::vector<std::vector<int>>& inverse) {
    int det = (matrix[0][0] * matrix[1][1] * matrix[2][2] +
               matrix[0][1] * matrix[1][2] * matrix[2][0] +
               matrix[0][2] * matrix[1][0] * matrix[2][1]) -
              (matrix[0][2] * matrix[1][1] * matrix[2][0] +
               matrix[0][0] * matrix[1][2] * matrix[2][1] +
               matrix[0][1] * matrix[1][0] * matrix[2][2]);

    if (det == 0) {
        std::cout << "Tidak dapat di inverse." << std::endl;
        return false;
    }

    int detInverse = -1;
    for (int i = 1; i < 26; ++i) {
        if ((det * i) % 26 == 1) {
            detInverse = i;
            break;
        }
    }

    if (detInverse == -1) {
        std::cout << "Tidak dapat di inverse." << std::endl;
        return false;
    }

    inverse.resize(MATRIX_SIZE, std::vector<int>(MATRIX_SIZE));

    inverse[0][0] = (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) * detInverse % 26;
    inverse[0][1] = (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2]) * detInverse % 26;
    inverse[0][2] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) * detInverse % 26;
    inverse[1][0] = (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2]) * detInverse % 26;
    inverse[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) * detInverse % 26;
    inverse[1][2] = (matrix[0][2] * matrix[1][0] - matrix[0][0] * matrix[1][2]) * detInverse % 26;
    inverse[2][0] = (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]) * detInverse % 26;
    inverse[2][1] = (matrix[0][1] * matrix[2][0] - matrix[0][0] * matrix[2][1]) * detInverse % 26;
    inverse[2][2] = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) * detInverse % 26;

    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            inverse[i][j] = (inverse[i][j] + 26) % 26;
        }
    }

    return true;
}

std::string encrypt(const std::string& plaintext, const std::vector<std::vector<int>>& keyMatrix) {
    std::string modifiedPlaintext = plaintext;
    int len = plaintext.length();

    while (len % MATRIX_SIZE != 0) {
        modifiedPlaintext += 'X';
        len++;
    }

    std::string ciphertext = "";

    for (int i = 0; i < len; i += MATRIX_SIZE) {
        std::vector<int> input(MATRIX_SIZE, 0);
        std::vector<int> output(MATRIX_SIZE, 0);

        for (int j = 0; j < MATRIX_SIZE; ++j)
            input[j] = modifiedPlaintext[i + j] - 'A';

        for (int j = 0; j < MATRIX_SIZE; ++j) {
            for (int k = 0; k < MATRIX_SIZE; ++k)
                output[j] += keyMatrix[j][k] * input[k];
            output[j] %= 26;
            ciphertext += (char)(output[j] + 'A');
        }
    }

    return ciphertext;
}

std::string decrypt(const std::string& ciphertext, const std::vector<std::vector<int>>& keyMatrix) {
    std::string decryptedText = "";
    int len = ciphertext.length();

    std::vector<std::vector<int>> inverseMatrix;
    if (!getMatrixInverse(keyMatrix, inverseMatrix))
        return "";

    for (int i = 0; i < len; i += MATRIX_SIZE) {
        std::vector<int> input(MATRIX_SIZE, 0);
        std::vector<int> output(MATRIX_SIZE, 0);

        for (int j = 0; j < MATRIX_SIZE; ++j)
            input[j] = ciphertext[i + j] - 'A';

        for (int j = 0; j < MATRIX_SIZE; ++j) {
            for (int k = 0; k < MATRIX_SIZE; ++k)
                output[j] += inverseMatrix[j][k] * input[k];
            output[j] %= 26;
            decryptedText += (char)((output[j] + 26) % 26 + 'A');
        }
    }

    return decryptedText;
}

int main() {
    std::vector<std::vector<int>> keyMatrix(MATRIX_SIZE, std::vector<int>(MATRIX_SIZE, 0));

    std::cout << "Masukkan kunci matriks (3x3):" << std::endl;
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            std::cout << "Masukkan elemen pada posisi (" << i + 1 << ", " << j + 1 << "): ";
            std::cin >> keyMatrix[i][j];
        }
    }

    while (true) {
        std::cout << "Hill Cipher Menu:" << std::endl;
        std::cout << "1. Encrypt" << std::endl;
        std::cout << "2. Decrypt" << std::endl;
        std::cout << "3. Cari Kunci Inverse" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Masukkan pilihan: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string plaintext;
                std::cout << "Masukkan plaintext (huruf kapital): ";
                std::cin >> plaintext;

                std::string ciphertext = encrypt(plaintext, keyMatrix);
                std::cout << "Cipher text: " << ciphertext << std::endl;
                break;
            }

            case 2: {
                std::string ciphertext;
                std::cout << "Masukkan ciphertext (huruf kapital): ";
                std::cin >> ciphertext;

                std::string decryptedText = decrypt(ciphertext, keyMatrix);
                std::cout << "Decrypted text: " << decryptedText << std::endl;
                break;
            }

            case 3: {
                std::vector<std::vector<int>> inverseMatrix;
                if (getMatrixInverse(keyMatrix, inverseMatrix)) {
                    std::cout << "Inverse Key Matrix:" << std::endl;
                    for (int i = 0; i < MATRIX_SIZE; ++i) {
                        for (int j = 0; j < MATRIX_SIZE; ++j) {
                            std::cout << inverseMatrix[i][j] << " ";
                        }
                        std::cout << std::endl;
                    }
                }
                break;
            }

            case 4:
                std::cout << "Exit program." << std::endl;
                return 0;

            default:
                std::cout << "Pilihan salah, coba lagi." << std::endl;
                break;
        }
    }

    return 0;
}
