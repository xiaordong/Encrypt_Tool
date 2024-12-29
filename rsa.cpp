//
// Created by Keith on 24-12-27.
//

#include "RSA.h"
#include <ctime>
#include <iostream>
#include <cmath>

RSA::RSA() {
    srand(static_cast<unsigned int>(time(NULL)));
}

int RSA::gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

bool RSA::isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int RSA::modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int RSA::findModInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        // q is quotient
        q = a / m;
        t = m;

        // m is remainder now, process same as Euclid's algo
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0)
        x1 += m0;

    return x1;
}

void RSA::genKey(int p, int q) {
    if (!isPrime(p) || !isPrime(q) || p < 2 || q < 2) {
        std::cerr << "Invalid Key Generation" << std::endl;
        return;
    }
    n = p * q;
    phi = (p - 1) * (q - 1);
    e = 3;
    while (gcd(e, phi) != 1) {
        e++;
    }
    d = findModInverse(e, phi);
}

std::vector<int> RSA::encrypt(const std::string& data) {
    std::vector<int> ciphertext;
    for (char ch : data) {
        int enChar = modExp(ch, e, n);
        ciphertext.push_back(enChar);
    }
    return ciphertext;
}

std::string RSA::decrypt(const std::vector<int>& ciphertext) {
    std::string decryptedText;
    for (int encryptedChar : ciphertext) {
        int decryptedChar = modExp(encryptedChar, d, n);
        decryptedText += static_cast<char>(decryptedChar);
    }
    return decryptedText;
}
