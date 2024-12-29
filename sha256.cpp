//
// Created by Keith on 24-12-26.
//

#include "sha256.h"
void sha256::update(const std::string &msg) {
    uint32_t msgWord[16];//32*16 = 512
    uint32_t i,j;
    uint64_t index = 0;
    while(index < msg.size()) {
        for (i = 0, j = 0; i < 16; i++) {
            msgWord[i] = (msg[index + (j++)] << 24) | (msg[index + (j++) + 1] << 16) | (msg[index + (j++) + 2] << 8)
            | msg[index + (j++) + 3];
        }
        transform(msgWord);
        index += 64;
    }
    uint64_t padLen = msg.size() * 8;
    index = 0;
    uint32_t padding[64];
    padding[0] = 0x80; // 添加一个1位

    // 填充消息，直到长度为448位（56字节）
    while (index < 56) {
        if (index == 0) {
            transform(padding); // 处理填充块
        } else {
            uint32_t block[16] = {0}; // 其他填充块为0
            transform(block);
        }
        index += 64; // 移动到下一个块
    }

    // 添加消息长度（以位为单位）
    uint8_t bits[8];
    bits[0] = (padLen >> 56) & 0xff;
    bits[1] = (padLen >> 48) & 0xff;
    bits[2] = (padLen >> 40) & 0xff;
    bits[3] = (padLen >> 32) & 0xff;
    bits[4] = (padLen >> 24) & 0xff;
    bits[5] = (padLen >> 16) & 0xff;
    bits[6] = (padLen >> 8) & 0xff;
    bits[7] = padLen & 0xff;

    transform((uint32_t*)bits);
}
