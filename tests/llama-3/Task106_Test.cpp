#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

class RSA {
private:
    static int gcd(int a, int b) {
        if (b == 0) return a;
        else return gcd(b, a % b);
    }

    static int multiplicativeInverse(int e, int phi) {
        int x = 0, y = 1;
        int a = phi, b = e;

        while (b != 0) {
            int q = a / b;
            int temp = b;
            b = a % b;
            a = temp;
            temp = x;
            x = y - q * x;
            y = temp;
        }

        if (y < 0) y += phi;
        return y;
    }

public:
    static pair<pair<int, int>, pair<int, int>> generateKeyPair(int p, int q) {
        int n = p * q;
        int phi = (p - 1) * (q - 1);

        random_device rd;
        mt19937 mt(rd());
        uniform_int_distribution<int> dist(1, phi - 1);

        int e = dist(mt);
        while (gcd(e, phi) != 1) {
            e = dist(mt);
        }

        int d = multiplicativeInverse(e, phi);
        return {{e, n}, {d, n}};
    }

    static vector<int> encrypt(pair<int, int> publicKey, string plaintext) {
        vector<int> cipher;
        for (char c : plaintext) {
            cipher.push_back(static_cast<int>(pow(c, publicKey.first)) % publicKey.second);
        }
        return cipher;
    }

    static string decrypt(pair<int, int> privateKey, vector<int> ciphertext) {
        string plain;
        for (int c : ciphertext) {
            plain += char(static_cast<int>(pow(c, privateKey.first)) % privateKey.second);
        }
        return plain;
    }
};

int main() {
    int p = 61;
    int q = 53;

    // Fixed primes for deterministic test
    auto keyPair = RSA::generateKeyPair(p, q);
    auto publicKey = keyPair.first;
    auto privateKey = keyPair.second;

    struct TestCase {
        string message;
    };

    TestCase tests[] = {
        {"HELLO"},
        {"WORLD"},
        {"TEST123"},
        {"RSA_ENCRYPTION"},
        {""}  // empty string test
    };

    for (auto& test : tests) {
        vector<int> encrypted = RSA::encrypt(publicKey, test.message);
        string decrypted = RSA::decrypt(privateKey, encrypted);

        cout << "Test message: \"" << test.message << "\"\n";
        cout << "Decrypted message: \"" << decrypted << "\"\n";

        if (decrypted == test.message) {
            cout << "Result: PASS\n\n";
        } else {
            cout << "Result: FAIL\n\n";
        }
    }

    return 0;
}
