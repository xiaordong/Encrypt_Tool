//
// Created by Keith on 24-12-26.
//

#ifndef SHA256_H
#define SHA256_H
#include <string>
#include <cstdint>


class sha256 {
public:
    //@detail 创建sha256类，包含常量值H[0],主循环的状态值
    sha256() {
        init();
    }
    ~sha256() {}
    void update(const std::string& msg);
    std::string final() {
        char buf[65]; // 用于存储结果字符串
        for (int i = 0; i < 8; i++) {
            sprintf(buf + (i * 8), "%08x", state[i]); // 将每个状态值转换为16进制字符串
        }
        buf[64] = 0; // 结束字符串
        return std::string(buf);
    }
    uint32_t state[8];
private:
    //@detail 初始化哈希值H[0]
    void init() {
        state[0] = 0x6a09e667;
        state[1] = 0xbb67ae85;
        state[2] = 0x3c6ef372;
        state[3] = 0xa54ff53a;
        state[4] = 0x510e527f;
        state[5] = 0x9b05688c;
        state[6] = 0x1f83d9ab;
        state[7] = 0x5be0cd19;
    }

    void transform(uint32_t msg[16]) {
        uint32_t a, b, c, d, e, f, g, h, i, j, t1, t2, m;
        uint32_t w[64]; // 扩展消息数组

        // 将输入消息块复制到w数组
        for (i = 0; i < 16; i++) {
            w[i] = msg[i];
        }

        // 扩展消息块到64个32位字
        for (i = 16; i < 64; i++) {
            m = w[i - 16];
            t1 = (m >> 7) ^ (m >> 18) ^ (m >> 3); // 计算t1
            m = w[i - 15];
            t2 = (m >> 17) ^ (m >> 19) ^ (m >> 10); // 计算t2
            w[i] = (t1 + w[i - 7] + t2 + w[i - 16]) & 0xffffffff; // 更新w[i]
        }
        a = state[0];
        b = state[1];
        c = state[2];
        d = state[3];
        e = state[4];
        f = state[5];
        g = state[6];
        h = state[7];
        for (i = 0; i < 64; i++) {
            t1 = h + ((e >> 6) ^ (e >> 11) ^ (e >> 25)) + ((e & f) ^ ((~e) & g)) + K[i] + w[i]; // 计算t1
            t2 = ((a >> 2) ^ (a >> 13) ^ (a >> 22)) + ((a & b) ^ (a & c) ^ (b & c)); // 计算t2
            h = g;
            g = f;
            f = e;
            e = (d + t1) & 0xffffffff;
            d = c;
            c = b;
            b = a;
            a = (t1 + t2) & 0xffffffff;
        }
        state[0] = (state[0] + a) & 0xffffffff;
        state[1] = (state[1] + b) & 0xffffffff;
        state[2] = (state[2] + c) & 0xffffffff;
        state[3] = (state[3] + d) & 0xffffffff;
        state[4] = (state[4] + e) & 0xffffffff;
        state[5] = (state[5] + f) & 0xffffffff;
        state[6] = (state[6] + g) & 0xffffffff;
        state[7] = (state[7] + h) & 0xffffffff;
    }
    //@detail 采用的常量
    const uint32_t K[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
        0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
        0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
        0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
        0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };
};


#endif //SHA256_H
