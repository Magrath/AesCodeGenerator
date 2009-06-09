typedef __m128i vector_type;

void aesECB(vector_type source[], vector_type dest[], vector_type * keys, vector_type enckey, int limit);
