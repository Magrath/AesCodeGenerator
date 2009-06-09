/* simple program for learning to use vector intrinsics */

#include <stdio.h>
#include <xmmintrin.h>
#include <stdlib.h>
#include <sys/time.h>

const int nkeys = 10;
const long size = 10000000;

typedef __m128i vector_type;
#define vec_op _mm_madd_epi16
#define vec_store _mm_stream_si128

//typedef __m128 vector_type;
//#define vec_op(_a, _b) _mm_shuffle_ps((_a), (_b), _MM_SHUFFLE(1,0,3,2)) 
//#define vec_store(_a, _b) _mm_stream_ps((float*)(_a), _b)

void fake_function1(vector_type source[], vector_type dest[], vector_type * keys, int limit)
{
  int i, j;

  for ( i = 0; i < limit; i++ ) {
    vector_type result = source[i];
    for ( j = 0; j < nkeys; j++ ) {
      result = vec_op(result, *(keys+j));
    }
    dest[i] = result;
  }

}

void fake_function2(vector_type source[], vector_type dest[], vector_type * keys, int limit)
{
  int i, j;

  for ( i = 0; i < limit; i++ ) {
    vector_type result = source[i];
    result = vec_op(result, *(keys+0));
    result = vec_op(result, *(keys+1));
    result = vec_op(result, *(keys+2));
    result = vec_op(result, *(keys+3));
    result = vec_op(result, *(keys+4));
    result = vec_op(result, *(keys+5));
    result = vec_op(result, *(keys+6));
    result = vec_op(result, *(keys+7));
    result = vec_op(result, *(keys+8));
    result = vec_op(result, *(keys+9));
    dest[i] = result;
  }
}

void fake_function3(vector_type source[], vector_type dest[], vector_type * keys, int limit)
{
  int i, j;

  vector_type key0 = keys[0];
  vector_type key1 = keys[1];
  vector_type key2 = keys[2];
  vector_type key3 = keys[3];
  vector_type key4 = keys[4];
  vector_type key5 = keys[5];
  vector_type key6 = keys[6];
  vector_type key7 = keys[7];
  vector_type key8 = keys[8];
  vector_type key9 = keys[9];

  for ( i = 0; i < limit; i++ ) {
    vector_type result = source[i];
    result = vec_op(result, key0);
    result = vec_op(result, key1);
    result = vec_op(result, key2);
    result = vec_op(result, key3);
    result = vec_op(result, key4);
    result = vec_op(result, key5);
    result = vec_op(result, key6);
    result = vec_op(result, key7);
    result = vec_op(result, key8);
    result = vec_op(result, key9);
    dest[i] = result;
  }
}

void fake_function4(vector_type source[], vector_type dest[], vector_type * keys, int limit)
{
  int i, j;

  vector_type key0 = keys[0];
  vector_type key1 = keys[1];
  vector_type key2 = keys[2];
  vector_type key3 = keys[3];
  vector_type key4 = keys[4];
  vector_type key5 = keys[5];
  vector_type key6 = keys[6];
  vector_type key7 = keys[7];
  vector_type key8 = keys[8];
  vector_type key9 = keys[9];

  for ( i = 0; i < limit; i++ ) {
    vector_type result = source[i];
    result = vec_op(result, key0);
    result = vec_op(result, key1);
    result = vec_op(result, key2);
    result = vec_op(result, key3);
    result = vec_op(result, key4);
    result = vec_op(result, key5);
    result = vec_op(result, key6);
    result = vec_op(result, key7);
    result = vec_op(result, key8);
    result = vec_op(result, key9);
    dest[i] = result;
    if ( i >= limit ) break;
    i++;
    result = source[i];
    result = vec_op(result, key0);
    result = vec_op(result, key1);
    result = vec_op(result, key2);
    result = vec_op(result, key3);
    result = vec_op(result, key4);
    result = vec_op(result, key5);
    result = vec_op(result, key6);
    result = vec_op(result, key7);
    result = vec_op(result, key8);
    result = vec_op(result, key9);
    dest[i] = result;
  }
}

void fake_function5(vector_type source[], vector_type dest[], vector_type * keys, int limit)
{
  int i, j;

  vector_type key0 = keys[0];
  vector_type key1 = keys[1];
  vector_type key2 = keys[2];
  vector_type key3 = keys[3];
  vector_type key4 = keys[4];
  vector_type key5 = keys[5];
  vector_type key6 = keys[6];
  vector_type key7 = keys[7];
  vector_type key8 = keys[8];
  vector_type key9 = keys[9];

  for ( i = 0; i < limit; i++ ) {
    vector_type result0 = source[i];
    result0 = vec_op(result0, key0);
    result0 = vec_op(result0, key1);
    result0 = vec_op(result0, key2);
    result0 = vec_op(result0, key3);
    result0 = vec_op(result0, key4);
    result0 = vec_op(result0, key5);
    result0 = vec_op(result0, key6);
    result0 = vec_op(result0, key7);
    result0 = vec_op(result0, key8);
    result0 = vec_op(result0, key9);
    dest[i] = result0;
    if ( i >= limit ) break;
    i++;
    vector_type result1 = source[i];
    result1 = vec_op(result1, key0);
    result1 = vec_op(result1, key1);
    result1 = vec_op(result1, key2);
    result1 = vec_op(result1, key3);
    result1 = vec_op(result1, key4);
    result1 = vec_op(result1, key5);
    result1 = vec_op(result1, key6);
    result1 = vec_op(result1, key7);
    result1 = vec_op(result1, key8);
    result1 = vec_op(result1, key9);
    dest[i] = result1;
  }
}

void fake_function6(vector_type source[], vector_type dest[], vector_type * keys, int limit)
{
  int i, j;

  vector_type key0 = keys[0];
  vector_type key1 = keys[1];
  vector_type key2 = keys[2];
  vector_type key3 = keys[3];
  vector_type key4 = keys[4];
  vector_type key5 = keys[5];
  vector_type key6 = keys[6];
  vector_type key7 = keys[7];
  vector_type key8 = keys[8];
  vector_type key9 = keys[9];

  for ( i = 0; i < limit; i+=2 ) {
    vector_type result0 = source[i];
    result0 = vec_op(result0, key0);
    result0 = vec_op(result0, key1);
    result0 = vec_op(result0, key2);
    result0 = vec_op(result0, key3);
    result0 = vec_op(result0, key4);
    result0 = vec_op(result0, key5);
    result0 = vec_op(result0, key6);
    result0 = vec_op(result0, key7);
    result0 = vec_op(result0, key8);
    result0 = vec_op(result0, key9);
    dest[i] = result0;
    vector_type result1 = source[i];
    result1 = vec_op(result1, key0);
    result1 = vec_op(result1, key1);
    result1 = vec_op(result1, key2);
    result1 = vec_op(result1, key3);
    result1 = vec_op(result1, key4);
    result1 = vec_op(result1, key5);
    result1 = vec_op(result1, key6);
    result1 = vec_op(result1, key7);
    result1 = vec_op(result1, key8);
    result1 = vec_op(result1, key9);
    dest[i] = result1;
  }
}

void fake_function7(vector_type source[], vector_type dest[], vector_type * keys, int limit)
{
  int i, j;

  vector_type key0 = keys[0];
  vector_type key1 = keys[1];
  vector_type key2 = keys[2];
  vector_type key3 = keys[3];
  vector_type key4 = keys[4];
  vector_type key5 = keys[5];
  vector_type key6 = keys[6];
  vector_type key7 = keys[7];
  vector_type key8 = keys[8];
  vector_type key9 = keys[9];

  for ( i = 0; i < limit; i+=2 ) {
    vector_type result0 = source[i];
    vector_type result1 = source[i+1];
    result0 = vec_op(result0, key0);
    result1 = vec_op(result1, key0);
    result0 = vec_op(result0, key1);
    result1 = vec_op(result1, key1);
    result0 = vec_op(result0, key2);
    result1 = vec_op(result1, key2);
    result0 = vec_op(result0, key3);
    result1 = vec_op(result1, key3);
    result0 = vec_op(result0, key4);
    result1 = vec_op(result1, key4);
    result0 = vec_op(result0, key5);
    result1 = vec_op(result1, key5);
    result0 = vec_op(result0, key6);
    result1 = vec_op(result1, key6);
    result0 = vec_op(result0, key7);
    result1 = vec_op(result1, key7);
    result0 = vec_op(result0, key8);
    result1 = vec_op(result1, key8);
    result0 = vec_op(result0, key9);
    result1 = vec_op(result1, key9);
    dest[i] = result0;
    dest[i+1] = result1; 
  }
}

void fake_function8(vector_type source[], vector_type dest[], vector_type * keys, int limit)
{
  int i, j;

  vector_type key0 = keys[0];
  vector_type key1 = keys[1];
  vector_type key2 = keys[2];
  vector_type key3 = keys[3];
  vector_type key4 = keys[4];
  vector_type key5 = keys[5];
  vector_type key6 = keys[6];
  vector_type key7 = keys[7];
  vector_type key8 = keys[8];
  vector_type key9 = keys[9];

  for ( i = 0; i < limit; i+=2 ) {
    vector_type result0 = source[i];
    vector_type result1 = source[i+1];
    result0 = vec_op(result0, key0);
    result1 = vec_op(result1, key0);
    result0 = vec_op(result0, key1);
    result1 = vec_op(result1, key1);
    result0 = vec_op(result0, key2);
    result1 = vec_op(result1, key2);
    result0 = vec_op(result0, key3);
    result1 = vec_op(result1, key3);
    result0 = vec_op(result0, key4);
    result1 = vec_op(result1, key4);
    result0 = vec_op(result0, key5);
    result1 = vec_op(result1, key5);
    result0 = vec_op(result0, key6);
    result1 = vec_op(result1, key6);
    result0 = vec_op(result0, key7);
    result1 = vec_op(result1, key7);
    result0 = vec_op(result0, key8);
    result1 = vec_op(result1, key8);
    result0 = vec_op(result0, key9);
    result1 = vec_op(result1, key9);
    vec_store(dest+i, result0);
    vec_store(dest+i+1, result1);
  }
}




void fake_function9(vector_type source[], vector_type dest[], vector_type * keys, int limit)
{
  int i, j;

  vector_type key0 = keys[0];
  vector_type key1 = keys[1];
  vector_type key2 = keys[2];
  vector_type key3 = keys[3];
  vector_type key4 = keys[4];
  vector_type key5 = keys[5];
  vector_type key6 = keys[6];
  vector_type key7 = keys[7];
  vector_type key8 = keys[8];
  vector_type key9 = keys[9];


  vector_type result0;
  vector_type result1;

  for ( i = 0; i < limit; i+=2 ) {
    result0 = vec_op(result0, key5);
    result1 = vec_op(result1, key0);
    result0 = vec_op(result0, key6);
    result1 = vec_op(result1, key1);
    result0 = vec_op(result0, key7);
    result1 = vec_op(result1, key2);
    result0 = vec_op(result0, key8);
    result1 = vec_op(result1, key3);
    result0 = vec_op(result0, key9);
    vec_store(dest+i, result0);
    result0 = source[i];
    result1 = vec_op(result1, key4);
    result0 = vec_op(result0, key0);
    result1 = vec_op(result1, key5);
    result0 = vec_op(result0, key1);
    result1 = vec_op(result1, key6);
    result0 = vec_op(result0, key2);
    result1 = vec_op(result1, key7);
    result0 = vec_op(result0, key3);
    result1 = vec_op(result1, key8);
    result0 = vec_op(result0, key4);
    result1 = vec_op(result1, key9);
    vec_store(dest+i+1, result1);
    result1 = source[i+1];    
  }
}



void fake_function10(vector_type source[], vector_type dest[], vector_type * keys, int limit)
{
  int i, j;

  vector_type key0 = keys[0];
  vector_type key1 = keys[1];
  vector_type key2 = keys[2];
  vector_type key3 = keys[3];
  vector_type key4 = keys[4];
  vector_type key5 = keys[5];
  vector_type key6 = keys[6];
  vector_type key7 = keys[7];
  vector_type key8 = keys[8];
  vector_type key9 = keys[9];

  for ( i = 0; i < limit; i+=2 ) {
    vector_type result0 = source[i];
    vector_type result1 = source[i+1];
    result0 = vec_op(result0, key0);
    result1 = vec_op(result1, key0);
    result0 = vec_op(result0, key1);
    result1 = vec_op(result1, key1);
    result0 = vec_op(result0, key2);
    result1 = vec_op(result1, key2);
    result0 = vec_op(result0, key3);
    result1 = vec_op(result1, key3);
    result0 = vec_op(result0, key4);
    result1 = vec_op(result1, key4);
    result0 = vec_op(result0, key5);
    result1 = vec_op(result1, key5);
    result0 = vec_op(result0, key6);
    result1 = vec_op(result1, key6);
    result0 = vec_op(result0, key7);
    result1 = vec_op(result1, key7);
    result0 = vec_op(result0, key8);
    result1 = vec_op(result1, key8);
    result0 = vec_op(result0, key9);
    result1 = vec_op(result1, key9);
    dest[i] = result0;
    dest[i+1] = result1;
  }
}


void fake_function11(vector_type source[], vector_type dest[], vector_type * keys, int limit)
{
  int i, j;

  vector_type key0 = keys[0];
  vector_type key1 = keys[1];
  vector_type key2 = keys[2];
  vector_type key3 = keys[3];
  vector_type key4 = keys[4];
  vector_type key5 = keys[5];
  vector_type key6 = keys[6];
  vector_type key7 = keys[7];
  vector_type key8 = keys[8];
  vector_type key9 = keys[9];

  vector_type * src_ptr = source;
  vector_type * dest_ptr = dest;
  vector_type * stop = source + limit;
  vector_type result0;
  vector_type result1;

  for ( ; src_ptr < stop; src_ptr += 2, dest_ptr += 2 ) {
    result0 = src_ptr[0];
    result1 = src_ptr[1];
    result0 = vec_op(result0, key0);
    result1 = vec_op(result1, key0);
    result0 = vec_op(result0, key1);
    result1 = vec_op(result1, key1);
    result0 = vec_op(result0, key2);
    result1 = vec_op(result1, key2);
    result0 = vec_op(result0, key3);
    result1 = vec_op(result1, key3);
    result0 = vec_op(result0, key4);
    result1 = vec_op(result1, key4);
    result0 = vec_op(result0, key5);
    result1 = vec_op(result1, key5);
    result0 = vec_op(result0, key6);
    result1 = vec_op(result1, key6);
    result0 = vec_op(result0, key7);
    result1 = vec_op(result1, key7);
    result0 = vec_op(result0, key8);
    result1 = vec_op(result1, key8);
    result0 = vec_op(result0, key9);
    result1 = vec_op(result1, key9);
    vec_store(dest_ptr, result0);
    vec_store(dest_ptr+1, result1);
  }
}



void fake_function12(vector_type source[], vector_type dest[], vector_type * keys, int limit)
{
  int i, j;

  vector_type key0 = keys[0];
  vector_type key1 = keys[1];
  vector_type key2 = keys[2];
  vector_type key3 = keys[3];
  vector_type key4 = keys[4];
  vector_type key5 = keys[5];
  vector_type key6 = keys[6];
  vector_type key7 = keys[7];
  vector_type key8 = keys[8];
  vector_type key9 = keys[9];

  vector_type * src_ptr = source;
  vector_type * dest_ptr = dest;
  vector_type * stop = source + limit;
  vector_type result0;
  vector_type result1;


  for ( ; src_ptr < stop; src_ptr += 2, dest_ptr += 2 ) {
    result0 = src_ptr[0];
    result1 = src_ptr[1];
    result0 = vec_op(result0, key0);
    result1 = vec_op(result1, key0);
    _mm_prefetch((char*)(src_ptr+32), _MM_HINT_NTA);
    result0 = vec_op(result0, key1);
    result1 = vec_op(result1, key1);
    result0 = vec_op(result0, key2);
    result1 = vec_op(result1, key2);
    result0 = vec_op(result0, key3);
    result1 = vec_op(result1, key3);
    result0 = vec_op(result0, key4);
    result1 = vec_op(result1, key4);
    result0 = vec_op(result0, key5);
    result1 = vec_op(result1, key5);
    result0 = vec_op(result0, key6);
    result1 = vec_op(result1, key6);
    result0 = vec_op(result0, key7);
    result1 = vec_op(result1, key7);
    result0 = vec_op(result0, key8);
    result1 = vec_op(result1, key8);
    result0 = vec_op(result0, key9);
    result1 = vec_op(result1, key9);
    vec_store(dest_ptr, result0);
    vec_store(dest_ptr+1, result1);
  }
}

void fake_function13(vector_type source[], vector_type dest[], vector_type * keys, int limit)
{
  int i, j;

  for ( i = 0; i < limit; i+=2 ) {
    vector_type result0 = source[i];
    vector_type result1 = source[i+1];
    for ( j = 0; j < nkeys; j++ ) {
      result0 = vec_op(result0, *(keys+j));
      result1 = vec_op(result1, *(keys+j));
    }
    dest[i] = result0;
    dest[i+1] = result1;
  }
}


void fake_function14(vector_type source[], vector_type dest[], vector_type * keys, int limit)
{
  int i, j;

  for ( i = 0; i < limit; i+=4 ) {
    vector_type result0 = source[i];
    vector_type result1 = source[i+1];
    vector_type result2 = source[i+2];
    vector_type result3 = source[i+3];
    for ( j = 0; j < nkeys; j++ ) {
      result0 = vec_op(result0, *(keys+j));
      result1 = vec_op(result1, *(keys+j));
      result2 = vec_op(result2, *(keys+j));
      result3 = vec_op(result3, *(keys+j));
    }
    dest[i] = result0;
    dest[i+1] = result1;
  }
}

void fake_function15(vector_type source[], vector_type dest[], vector_type * keys, int limit)
{
  int i, j;

  for ( i = 0; i < limit; i+=4 ) {
    vector_type result0 = source[i];
    vector_type result1 = source[i+1];
    vector_type result2 = source[i+2];
    vector_type result3 = source[i+3];
    for ( j = 0; j < nkeys; j++ ) {
      vector_type key = *(keys+j);
      result0 = vec_op(result0, key);
      result1 = vec_op(result1, key);
      result2 = vec_op(result2, key);
      result3 = vec_op(result3, key);
    }
    dest[i] = result0;
    dest[i+1] = result1;
    dest[i+2] = result2;
    dest[i+3] = result3;
  }
}

void fake_function16(vector_type source[], vector_type dest[], vector_type * keys, int limit)
{
  int i, j;

  for ( i = 0; i < limit; i+=7 ) {
    vector_type result0 = source[i];
    vector_type result1 = source[i+1];
    vector_type result2 = source[i+2];
    vector_type result3 = source[i+3];
    vector_type result4 = source[i+4];
    vector_type result5 = source[i+5];
    vector_type result6 = source[i+6];
    for ( j = 0; j < nkeys; j++ ) {
      vector_type key = *(keys+j);
      result0 = vec_op(result0, key);
      result1 = vec_op(result1, key);
      result2 = vec_op(result2, key);
      result3 = vec_op(result3, key);
      result4 = vec_op(result4, key);
      result5 = vec_op(result5, key);
      result6 = vec_op(result6, key);
    }
    dest[i] = result0;
    dest[i+1] = result1;
    dest[i+2] = result2;
    dest[i+3] = result3;
    dest[i+4] = result4;
    dest[i+5] = result5;
    dest[i+6] = result6;
  }
}

void fake_function17(vector_type source[], vector_type dest[], vector_type * keys, int limit)
{
  int i, j;

  for ( i = 0; i < limit; i+=7 ) {
    vector_type result0 = source[i];
    vector_type result1 = source[i+1];
    vector_type result2 = source[i+2];
    vector_type result3 = source[i+3];
    vector_type result4 = source[i+4];
    vector_type result5 = source[i+5];
    vector_type result6 = source[i+6];
    for ( j = 0; j < nkeys; j++ ) {
      vector_type key = *(keys+j);
      result0 = vec_op(result0, key);
      result1 = vec_op(result1, key);
      result2 = vec_op(result2, key);
      result3 = vec_op(result3, key);
      result4 = vec_op(result4, key);
      result5 = vec_op(result5, key);
      result6 = vec_op(result6, key);
    }
    dest[i] = result0;
    dest[i+1] = result1;
    dest[i+2] = result2;
    dest[i+3] = result3;
    dest[i+4] = result4;
    dest[i+5] = result5;
    dest[i+6] = result6;
  }
}


void fake_function18(vector_type source[], vector_type dest[], vector_type * keys, int limit)
{
  int i, j;

  vector_type key0 = keys[0];
  vector_type key1 = keys[1];
  vector_type key2 = keys[2];
  vector_type key3 = keys[3];
  vector_type key4 = keys[4];
  vector_type key5 = keys[5];
  vector_type key6 = keys[6];
  vector_type key7 = keys[7];
  vector_type key8 = keys[8];
  vector_type key9 = keys[9];

  for ( i = 0; i < limit; i+=3 ) {
    vector_type result0 = source[i];
    vector_type result1 = source[i+1];
    vector_type result2 = source[i+2];
    result0 = vec_op(result0, key0);
    result1 = vec_op(result1, key0);
    result2 = vec_op(result2, key0);

    result0 = vec_op(result0, key1);
    result1 = vec_op(result1, key1);
    result2 = vec_op(result2, key1);

    result0 = vec_op(result0, key2);
    result1 = vec_op(result1, key2);
    result2 = vec_op(result2, key2);

    result0 = vec_op(result0, key3);
    result1 = vec_op(result1, key3);
    result2 = vec_op(result2, key3);

    result0 = vec_op(result0, key4);
    result1 = vec_op(result1, key4);
    result2 = vec_op(result2, key4);

    result0 = vec_op(result0, key5);
    result1 = vec_op(result1, key5);
    result2 = vec_op(result2, key5);

    result0 = vec_op(result0, key6);
    result1 = vec_op(result1, key6);
    result2 = vec_op(result2, key6);

    result0 = vec_op(result0, key7);
    result1 = vec_op(result1, key7);
    result2 = vec_op(result2, key7);

    result0 = vec_op(result0, key8);
    result1 = vec_op(result1, key8);
    result2 = vec_op(result2, key8);

    result0 = vec_op(result0, key9);
    result1 = vec_op(result1, key9);
    result2 = vec_op(result2, key9);

    vec_store(dest+i, result0);
    vec_store(dest+i+1, result1);
    vec_store(dest+i+2, result2);
  }
}

void fake_function19(vector_type source[], vector_type dest[], vector_type * keys, int limit)
{
  int i, j;

  vector_type key0 = keys[0];
  vector_type key1 = keys[1];
  vector_type key2 = keys[2];
  vector_type key3 = keys[3];
  vector_type key4 = keys[4];
  vector_type key5 = keys[5];
  vector_type key6 = keys[6];
  vector_type key7 = keys[7];
  vector_type key8 = keys[8];
  vector_type key9 = keys[9];

  for ( i = 0; i < limit; i+=4 ) {
    vector_type result0 = source[i];
    vector_type result1 = source[i+1];
    vector_type result2 = source[i+2];
    vector_type result3 = source[i+3];

    result0 = vec_op(result0, key0);
    result1 = vec_op(result1, key0);
    result2 = vec_op(result2, key0);
    result3 = vec_op(result3, key0);

    result0 = vec_op(result0, key1);
    result1 = vec_op(result1, key1);
    result2 = vec_op(result2, key1);
    result3 = vec_op(result3, key1);

    result0 = vec_op(result0, key2);
    result1 = vec_op(result1, key2);
    result2 = vec_op(result2, key2);
    result2 = vec_op(result3, key2);

    result0 = vec_op(result0, key3);
    result1 = vec_op(result1, key3);
    result2 = vec_op(result2, key3);
    result3 = vec_op(result3, key3);

    result0 = vec_op(result0, key4);
    result1 = vec_op(result1, key4);
    result2 = vec_op(result2, key4);
    result3 = vec_op(result3, key4);

    result0 = vec_op(result0, key5);
    result1 = vec_op(result1, key5);
    result2 = vec_op(result2, key5);
    result3 = vec_op(result3, key5);

    result0 = vec_op(result0, key6);
    result1 = vec_op(result1, key6);
    result2 = vec_op(result2, key6);
    result3 = vec_op(result3, key6);

    result0 = vec_op(result0, key7);
    result1 = vec_op(result1, key7);
    result2 = vec_op(result2, key7);
    result3 = vec_op(result3, key7);

    result0 = vec_op(result0, key8);
    result1 = vec_op(result1, key8);
    result2 = vec_op(result2, key8);
    result3 = vec_op(result3, key8);

    result0 = vec_op(result0, key9);
    result1 = vec_op(result1, key9);
    result2 = vec_op(result2, key9);
    result3 = vec_op(result3, key9);

    vec_store(dest+i, result0);
    vec_store(dest+i+1, result1);
    vec_store(dest+i+2, result2);
    vec_store(dest+i+2, result3);
  }
}

void initialize_data(vector_type * array, int size)
{
  long i;
  char * a = (char*) array;

  for ( i = 0; i < size * sizeof(vector_type); i++ ) {
    a[i] = i;
  }
}

int vectorLearning()
{
  vector_type * orig;
  vector_type * vnew;
  vector_type keys[nkeys];
  struct timeval start_time;
  struct timeval stop_time;
  long long sort_time;
  int sum, i;

  orig =  (vector_type *) _mm_malloc(sizeof(vector_type)*size, 16);
  vnew =  (vector_type *) _mm_malloc(sizeof(vector_type)*size, 16);

  initialize_data(orig, size);
  initialize_data(vnew, size);
  initialize_data(keys, nkeys);

  /* record starting time */
  gettimeofday(&start_time, NULL);

  fake_function10(orig, vnew, keys, size);

  /* record finishing time */
  gettimeofday(&stop_time, NULL);
  sort_time = (stop_time.tv_sec - start_time.tv_sec) * 1000000L +
    (stop_time.tv_usec - start_time.tv_usec);

  for ( i = 0; i < size; i++ ) {
    sum = sum + ((int*)vnew)[i];
  }

  printf("Time is %lld, sum is %d\n", sort_time, sum);

  return 0;
}
