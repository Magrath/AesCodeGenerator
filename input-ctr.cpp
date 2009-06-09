#include <xmmintrin.h> // SSE
#include <emmintrin.h> // SSE2
#include <pmmintrin.h> // SSE3

#ifndef __APPLE__
#include "papiex.h"
#endif
#include "aes.h"
#include "Quad.h"
#include "utils.h"
#include <iostream>
#include <sys/time.h>
const int nKeys = 14;

#define vector_store    _mm_stream_si128
#define LATENCY 0

typedef __m128i vector_type;

#if LATENCY == 2
#define encrypt_initial  _mm_madd_epi16    // latency==2
#define encrypt_round    _mm_madd_epi16    // latency==2
#define encrypt_final    _mm_madd_epi16    // latency==2
#elif LATENCY == 3
#define encrypt_initial  _mm_sad_epu8      // latency==3
#define encrypt_round    _mm_sad_epu8      // latency==3
#define encrypt_final    _mm_sad_epu8      // latency==3
#elif LATENCY == 5
#define encrypt_initial(i,j)    (__m128i)_mm_mul_sd((__m128d) i,(__m128d) j) // latency==5
#define encrypt_round(i,j)      (__m128i)_mm_mul_sd((__m128d) i,(__m128d) j) // latency==5
#define encrypt_final(i,j)      (__m128i)_mm_mul_sd((__m128d) i,(__m128d) j) // latency==5
#else
#define encrypt_initial aes256_encrypt_initialround_m128
#define encrypt_round   aes256_encrypt_round_m128
#define encrypt_final   aes256_encrypt_finalround_m128
#endif

void aesCTR(vector_type source[], vector_type dest[], vector_type * keys, 
            vector_type nonce, vector_type enckey, int limit)
{
#ifndef __APPLE__
    PAPIEX_START();
#else
    struct timeval start_time;
    struct timeval stop_time;
    gettimeofday(&start_time,NULL);
#endif
    unsigned int i;
    
    #pragma omp parallel for 
    for ( i = 0; i < limit; i++ ) {
        vector_type result;
        
        #if LATENCY == 0
        result = Quad(nonce).increment(i).data;
        #else
        result = _mm_add_epi64(nonce,_mm_set_epi32(0,0,0,i)); 
        #endif

        // initial round
        result = encrypt_initial(result, enckey);    
        
        // encryption
        for (int j = 1; j < nKeys; j++ ) {
            result = encrypt_round(result, *(keys+j));
        }
        
        // final round
        result = encrypt_final(result, *keys);
        
        result = _mm_xor_si128(result,source[i]);

        dest[i] = result;
    } // end outer loop
#ifndef __APPLE__    
    PAPIEX_STOP();
#else    
    gettimeofday(&stop_time, NULL);
    long long timeTaken = (stop_time.tv_sec - start_time.tv_sec) * 1000000L + (stop_time.tv_usec - start_time.tv_usec);
    printf("%lld\n", timeTaken);
#endif
}
