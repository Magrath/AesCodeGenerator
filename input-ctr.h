typedef __m128i vector_type;

void aesCTR(vector_type source[], vector_type dest[], vector_type * keys, 
            vector_type nonce, vector_type enckey, int limit);
