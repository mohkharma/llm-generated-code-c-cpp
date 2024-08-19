#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

string encrypt(const string& message, const string& key) {
    // Generate a random seed for the cipher
    srand(time(nullptr));

    // Create a cipher (e.g., simple substitution cipher for demonstration)
    vector<char> cipher(256);
    for (int i = 0; i < 256; ++i) {
        cipher[i] = i;
    }

    // Shuffle the cipher using the secret key
    for (size_t i = 0; i < key.length(); ++i) {
        int j = rand() % 256;
        swap(cipher[i], cipher[j]);
    }

    // Encrypt the message
    string encrypted_message;
    for (char c : message) {
        encrypted_message += cipher[c];
    }

    return encrypted_message;
}

int main() {
    string message = "Hello, world!";
    string secret_key = "mysecretkey";

    string encrypted = encrypt(message, secret_key);
    cout << encrypted << endl;

    return 0;
}
