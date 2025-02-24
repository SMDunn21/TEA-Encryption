#include <cstdint>

using namespace std;

//Function to Encrypt
void encrypt(uint32_t plain[2], uint32_t key[4]){
    uint32_t delta = 0x9E3779B9;
    uint32_t sum = 0;
    uint32_t l = plain[0], r = plain[1];

    for(int i = 0; i < 32; ++i){
        sum += delta;
        l += ((r << 4) + key[0]) ^ (r + sum) ^ ((r >> 5) + key[1]);
        r += ((l << 4) + key[2]) ^ (l + sum) ^ ((l >> 5) + key[3]);
    }

    plain[0] = l;
    plain[1] = r;
}

//Function to Decrypt
void decrypt(uint32_t cipher[2], uint32_t key[4]){
    uint32_t delta = 0x9E3779B9;
    uint32_t sum = delta << 5;
    uint32_t l = cipher[0], r = cipher[1];

    for(int i = 0; i < 32; ++i){
        r += ((l << 4) + key[2]) ^ (l - sum) ^ ((l >> 5) + key[3]);
        l += ((r << 4) + key[0]) ^ (r - sum) ^ ((r >> 5) + key[1]);
        sum -= delta;
    }

    cipher[0] = l;
    cipher[1] = r;
}

int main(){
    return 0;
}