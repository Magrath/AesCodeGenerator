/*
 *  aes.h
 *  FYP
 *
 *  Created by Paul Magrath on 09/11/2008.
 *  Copyright 2008 Paul Magrath. All rights reserved.
 *
 */

#ifndef AES_H
#define AES_H
#include <xmmintrin.h>
#include "aes256.h"

#ifdef __cplusplus
extern "C" { 
#endif

    typedef unsigned int aes_mode;
    #define ECB 0
    #define CTR 1
    
    int aesDemo (const aes_mode mode, const char* filename, bool verbose);

    void aes256_decrypt(unsigned char* buf, const unsigned char* key, const unsigned int length);
    void aes256_encrypt(unsigned char* buf, const unsigned char* key, const unsigned int length);

    __m128i aes256_decrypt_block(const __m128i keys[14], const uint8_t* deckey, __m128i buf);
    __m128i aes256_encrypt_block(const __m128i keys[14], const uint8_t* enckey, __m128i buf);

    void aes256_decrypt_keygen_m128(__m128i keys[14], const uint8_t* deckey);
    void aes256_encrypt_keygen_m128(__m128i keys[14], const uint8_t* enckey);

    __m128i aes256_decrypt_initialround_m128(__m128i buffer, const uint8_t* deckey);
    __m128i aes256_decrypt_round_m128(__m128i buffer, const __m128i roundkey);
    __m128i aes256_decrypt_finalround_m128(__m128i buffer, const __m128i roundkey);

    __m128i aes256_encrypt_initialround_m128(__m128i buffer, const __m128i enckey);
    __m128i aes256_encrypt_round_m128(__m128i buffer, const __m128i roundkey);
    __m128i aes256_encrypt_finalround_m128(__m128i buffer, const __m128i roundkey);
    
#ifdef __cplusplus
}
#endif    

#endif
