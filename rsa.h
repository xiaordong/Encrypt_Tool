//
// Created by Keith on 24-12-27.
//

#ifndef RSA_H
#define RSA_H
#include <vector>
#include <string>

class RSA {
public:
    RSA();
    void genKey(int p, int q);
    std::vector<int> encrypt(const std::string& data);
    std::string decrypt(const std::vector<int>& data);
private:
    int gcd(int a, int b);
    bool isPrime(int n);
    int modExp(long long base, long long exp, long long mod);
    int findModInverse(int a, int m);
    int n, e, d; // n = pq, e is the public exponent, d is the private exponent
    int phi; // Euler's totient function value, (p-1)*(q-1)
};

#endif // RSA_H
