#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

// Your original functions (unchanged):

bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int generate_prime(int min_val, int max_val) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min_val, max_val);
    int prime = dis(gen);
    while (!is_prime(prime)) {
        prime = dis(gen);
    }
    return prime;
}

int mod_inverse(int a, int m) {
    for (int i = 1; i < m; i++) {
        if ((a * i) % m == 1) return i;
    }
    return -1;
}

pair<pair<int, int>, pair<int, int>> generate_keypair(int p, int q) {
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e = 2;
    while (e < phi) {
        if (__gcd(e, phi) == 1) break;
        e++;
    }
    int d = mod_inverse(e, phi);
    return make_pair(make_pair(e, n), make_pair(d, n));
}

vector<int> encrypt(pair<int, int> pk, string plaintext) {
    int key = pk.first;
    int n = pk.second;
    vector<int> cipher;
    for (char c : plaintext) {
        cipher.push_back(static_cast<int>(fmod(pow(static_cast<double>(c), key), n)));
    }
    return cipher;
}

string decrypt(pair<int, int> pk, vector<int> ciphertext) {
    int key = pk.first;
    int n = pk.second;
    string plain;
    for (int c : ciphertext) {
        plain += static_cast<char>(fmod(pow(static_cast<double>(c), key), n));
    }
    return plain;
}

// Test driver with fixed primes and test cases:

int main() {
    // Fixed primes for deterministic testing:
    int p = 1013;
    int q = 2029;

    auto keypair = generate_keypair(p, q);
    auto public_key = keypair.first;
    auto private_key = keypair.second;

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
        auto encrypted_msg = encrypt(public_key, test.message);
        string decrypted_msg = decrypt(private_key, encrypted_msg);

        cout << "Test message: \"" << test.message << "\"\n";
        cout << "Decrypted: \"" << decrypted_msg << "\"\n";

        if (decrypted_msg == test.message) {
            cout << "Result: PASS\n\n";
        } else {
            cout << "Result: FAIL\n\n";
        }
    }

    return 0;
}
