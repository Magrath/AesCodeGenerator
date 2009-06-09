#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "aes.h"
#include "aes256.h"
#include "utils.h"
#include "Quad.h"

#define USE_INPUT_C
#ifdef  USE_INPUT_C
#include <sys/time.h>
#include "input-ctr.h"
#include "input-ecb.h"
#endif

__m128i aes256_decrypt_initialround_m128(__m128i buf, const uint8_t* deckey){
    Quad buffer = Quad(buf);

    aes_addRoundKey(buffer.c,deckey);
    aes_shiftRows_inv(buffer.c);
    aes_subBytes_inv(buffer.c);
    
    return buffer.data;
}  /* aes256_decrypt_initialround_m128 */

void aes256_decrypt_keygen_m128(__m128i keys[14], const uint8_t* deckey){

    uint8_t key[32];
    uint8_t rcon = 0x80;
    
    register uint8_t i = 16;
    while (i--)  (key[i] = deckey[i]), key[16+i] = deckey[16 + i];

    for (i=13; i>0; i--){
        if( ( (i) & 1 ) )           
        {
            aes_expandDecKey(key, &rcon);
            keys[i] = Quad(&key[16]).data;
        }
        else {
            keys[i] = Quad(&key[0]).data;
        }
    }
    keys[0] = Quad(key).data;
} /* aes256_decrypt_keygen_m128 */

__m128i aes256_encrypt_initialround_m128(__m128i buf, const __m128i encryption_key){
    return _mm_xor_si128(buf,encryption_key);
} /* aes256_encrypt_initialround_m128 */

void aes256_encrypt_keygen_m128(__m128i keys[14], const uint8_t* enckey){

    uint8_t key[32];
    uint8_t rcon = 1;
    
    register uint8_t i = 16;
    while (i--)  (key[i] = enckey[i]), key[16+i] = enckey[16 + i];
    
    for (i=1; i<14; i++){
        if( i & 1 ) {
            keys[i] = Quad(&key[16]).data;
        }
        else {
            aes_expandEncKey(key, &rcon);
            keys[i] = Quad(&key[0]).data;
        }
    } 
    aes_expandEncKey(key, &rcon); 
    keys[0] = Quad(key).data;
} /* aes256_encrypt_keygen_m128 */

__m128i aes256_encrypt_round_m128(__m128i b, const __m128i k){
    Quad buffer = Quad(b);
    const Quad key = Quad(k);
    aes256_encrypt_round(buffer.c, key.c);
    return buffer.data;
} /* aes256_encrypt_round_m128 */

__m128i aes256_encrypt_finalround_m128(__m128i b, const __m128i k){
    Quad buffer = Quad(b);
    const Quad key = Quad(k);
    aes256_encrypt_finalround(buffer.c, key.c);
    return buffer.data;
} /* aes256_encrypt_finalround_m128 */

__m128i aes256_decrypt_round_m128(__m128i b, const __m128i k){
    Quad buffer = Quad(b);
    const Quad key = Quad(k);
    aes256_decrypt_round(buffer.c, key.c);
    return buffer.data;
} /* aes256_decrypt_round_m128 */

__m128i aes256_decrypt_finalround_m128(__m128i b, const __m128i k){
    Quad buffer = Quad(b);
    const Quad key = Quad(k);
    aes256_decrypt_finalround(buffer.c, key.c);
    return buffer.data;
} /* aes256_decrypt_finalround_m128 */

__m128i aes256_encrypt_block(const __m128i keys[14], const uint8_t* enckey, __m128i buf){
    
    // initial round
    buf = aes256_encrypt_initialround_m128(buf, Quad(enckey).data);    
    
    // do encryption
    for (int i=1; i<14; i++){
        buf = aes256_encrypt_round_m128(buf, keys[i]);
    }
    
    // final round
    buf = aes256_encrypt_finalround_m128(buf, keys[0]);
    
    return buf;
    
} /* encrypt_block */

__m128i aes256_decrypt_block(const __m128i keys[14], const uint8_t* deckey, __m128i buf){
    
    // initial round
    buf = aes256_decrypt_initialround_m128(buf, deckey);
    
    // do decryption
    for (int i=13; i>0; i--){
        buf = aes256_decrypt_round_m128(buf, keys[i]);
    }
    
    // final round
    buf = aes256_decrypt_finalround_m128(buf, keys[0]);
    
    return buf;
} /* decrypt_block */

void aes256_encrypt(unsigned char* buf, const unsigned char* key, const unsigned int mode, const __m128i nonce, const unsigned int length){
    unsigned int i,j;
    unsigned char* p;
    aes256_context ctx; 
    
    __m128i source[(length/16)+1];
    __m128i dest[(length/16)+1];
    __m128i keys[14];
    
    aes256_init(&ctx, key);
    for (i=0,j=0; i < length; j++){
        p = &(buf[i]);
        source[j] = Quad(p).data;
        i+=16;
    }
    
    __m128i enckey = Quad(ctx.enckey).data;
    
    if (mode == ECB) {
        aes256_encrypt_keygen_m128(keys, ctx.enckey);
        #ifdef USE_INPUT_C
        aesECB(source, dest, keys, enckey,j);
        #endif
    } else if (mode == CTR){
        aes256_encrypt_keygen_m128(keys, ctx.enckey);
        #ifdef USE_INPUT_C
        aesCTR(source, dest, keys, nonce, enckey,j);
        #endif
    } 

    #ifndef USE_INPUT_C
    __m128i counter = nonce;    
    #endif
    for (i=0; i<j; i++){
        p = &(buf[i*16]);
        #ifndef USE_INPUT_C
        if (mode == ECB)
            dest[i] = aes256_encrypt_block(keys, ctx.enckey,source[i]);
        else if (mode == CTR){
            __m128i result = counter;
            dest[i] = _mm_xor_si128(aes256_encrypt_block(keys, ctx.enckey,result),source[i]);
            counter = Quad(counter).increment().data;
        }
        #endif
        Quad(dest[i]).toArray(p);
    }
    aes256_done(&ctx);    
} /* encrypt */

void aes256_decrypt(unsigned char* buf, const unsigned char* key, const unsigned int mode, const __m128i nonce, const unsigned int length){
    unsigned int i,j;
    unsigned char* p;
    aes256_context ctx; 
    
    __m128i source[(length/16)+1];
    __m128i dest[(length/16)+1];
    __m128i keys[14];
    
    aes256_init(&ctx, key);
    for (i=0,j=0; i < length; j++){
        p = &(buf[i]);
        source[j] = Quad(p).data;
        i+=16;
    }
    
    if (mode == ECB)
        aes256_decrypt_keygen_m128(keys, ctx.deckey);
    else if (mode == CTR)
        aes256_encrypt_keygen_m128(keys, ctx.enckey);
    
    __m128i counter = nonce;
    for (i=0; i<j; i++){
        p = &(buf[i*16]);
        if (mode == ECB)
            dest[i] = aes256_decrypt_block(keys, ctx.deckey,source[i]);
        else if (mode == CTR){
            __m128i result = counter;
            dest[i] = _mm_xor_si128(aes256_encrypt_block(keys, ctx.enckey,result),source[i]);
            counter = Quad(counter).increment().data;
        }
        Quad(dest[i]).toArray(p);
    }
    
    aes256_done(&ctx);    
} /* decrypt */

int aesDemo (aes_mode mode, const char* filename, bool verbose)
{
    int i;
    
    unsigned char key[] = {
        0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81,
        0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4
    };
    /*unsigned char nist_test_plaintext[] = {
        0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a, 
        0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c, 0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51
    };*/
    unsigned char initialization_vector[] = {
        0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 
        0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
    };
    
    const std::string   str     = readFile(filename);    
    unsigned char *     ptr     = (unsigned char*) str.c_str();
    __m128i             nonce   = Quad(initialization_vector).data;
    int                 length  = str.length();
    
    //length = 32; ptr = nist_test_plaintext; mode = CTR; // NIST CTR-AES256.Encrypt test vector
    
    /* do AES */
    if (verbose){
        std::cout << "string:        \t" << ptr << "\n";
        DUMP("Plaintext: \t", i, ptr, length);
    }
    aes256_encrypt(ptr, key, mode, nonce, length);
    if (verbose){
        DUMP("Ciphertext:\t", i, ptr, length);
    	aes256_decrypt(ptr, key, mode, nonce, length);
        DUMP("Plaintext: \t", i, ptr, length);
        std::cout << "string:        \t" << ptr << "\n";
    
    	if (str.compare((const char*)ptr) == 0){
            cout << "\nThis was a triumph.\n";
            cout << "I'm making a note here: HUGE SUCCESS.\n";
        }
        else{
            //cout << "Success\n";
        }
    }
    
    return 0;
} /* aesDemo */
