/*
Author: Sean Dunn
Date: 2/24/2025

This is a program to perform the TEA encryption and decryption algorithm

*/



#include <cstdint>
#include <iostream>

using namespace std;

//Function to Encrypt
void encrypt(uint32_t plain[2], uint32_t key[4]){
    //Set initial values
    uint32_t delta = 0x9E3779B9;
    uint32_t sum = 0;
    uint32_t l = plain[0], r = plain[1];

    //Run 32 rounds of operations
    for(int i = 0; i < 32; ++i){
        sum += delta;
        l += ((r << 4) + key[0]) ^ (r + sum) ^ ((r >> 5) + key[1]);
        r += ((l << 4) + key[2]) ^ (l + sum) ^ ((l >> 5) + key[3]);
    }

    //Set text array to new value
    plain[0] = l;
    plain[1] = r;
}

//Function to Decrypt
void decrypt(uint32_t cipher[2], uint32_t key[4]){
    //Set initial values
    uint32_t delta = 0x9E3779B9;
    uint32_t sum = delta << 5;
    uint32_t l = cipher[0], r = cipher[1];

    //Run 32 rounds of operations
    for(int i = 0; i < 32; ++i){
        r -= ((l << 4) + key[2]) ^ (l + sum) ^ ((l >> 5) + key[3]);
        l -= ((r << 4) + key[0]) ^ (r + sum) ^ ((r >> 5) + key[1]);
        sum -= delta;
    }

    //Set text array to new value
    cipher[0] = l;
    cipher[1] = r;
}

int main(){
    //Set Text and Key Values
    uint32_t text[2] = {0x01CA4567, 0x0CABCDEF};
    uint32_t k[4] = {0xAF6BABCD, 0xEF00F000, 0xFEAFAFAF, 0xACCDEF01}; 

    //Display Plaintext, encrypt, then display Ciphertext
    std::cout << std::hex << text[0] << text[1] << "\n";
    encrypt(text, k);
    std::cout << std::hex << text[0] << text[1] << "\n";
    decrypt(text, k);
    std::cout << std::hex << text[0] << text[1] << "\n";
    return 0;

    //In order to allow for larger blocks of text, I would write a function that took an input of arbitrary length, break it up into an array of uint32_t types, and pass that into the encryption funtion to process 2 at a time by looping through the array.
}