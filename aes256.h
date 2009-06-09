/*  
*   Byte-oriented AES-256 implementation.
*   All lookup tables replaced with 'on the fly' calculations. 
*
*   Copyright (c) 2007 Ilya O. Levin, http://www.literatecode.com
*
*   Permission to use, copy, modify, and distribute this software for any
*   purpose with or without fee is hereby granted, provided that the above
*   copyright notice and this permission notice appear in all copies.
*
*   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
*   WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
*   MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
*   ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
*   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
*   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
*   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#ifndef AES256_H
#define AES256_H

#ifndef _UINT8_T
#define _UINT8_T
typedef unsigned char         uint8_t;
#endif /*_UINT8_T */

#ifdef __cplusplus
extern "C" { 
#endif

    typedef struct {
        uint8_t key[32]; 
        uint8_t enckey[32]; 
        uint8_t deckey[32];
        
        // previously local variables
        uint8_t rcon;
        uint8_t currRound;
    } aes256_context; 

    // ilya's methods.
    void aes256_init(aes256_context *, const uint8_t * /* key */);
    void aes256_done(aes256_context *);
    void aes256_encrypt_ecb(aes256_context *, uint8_t * /* plaintext */);
    void aes256_decrypt_ecb(aes256_context *, uint8_t * /* cipertext */);
    
    // previously private
    void aes_expandEncKey(uint8_t *k, uint8_t *rc);
    void aes_expandDecKey(uint8_t *k, uint8_t *rc);
    void aes_addRoundKey(uint8_t *buf, const uint8_t *key);
    void aes_addRoundKey_cpy(uint8_t *buf, const uint8_t *key, uint8_t *cpk);
    void aes_subBytes_inv(uint8_t *buf);
    void aes_shiftRows_inv(uint8_t *buf);
    
    // my own methods.
    void aes256_encrypt_init(aes256_context *ctx, uint8_t *buf);
    void aes256_encrypt_round(uint8_t *buf, const uint8_t* roundKey);
    void aes256_encrypt_finalround(uint8_t *buf, const uint8_t* roundKey);
    void aes256_decrypt_init(aes256_context *ctx, uint8_t *buf);
    void aes256_decrypt_round(uint8_t *buf, const uint8_t* roundKey);
    void aes256_decrypt_finalround(uint8_t *buf, const uint8_t* roundKey);
    
#ifdef __cplusplus
}
#endif

#endif
