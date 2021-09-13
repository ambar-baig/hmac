#ifndef MD5_H
#define MD5_H

#include<stdint.h>

typedef struct{
    uint32_t state[4];  /* A, B, C, D Partial Digest */
    uint32_t count[2];  /* MSB bits, LSB bits 64 bits = 32 bits + 32 bits */
    uint8_t buffer[64]; /* Message Block Size 64 x 8 = 512 bits */
    uint8_t digest[16]; /* Digest Size 16 x 8 = 128 bits */
}MD5_context;

uint8_t* MD5(const uint8_t* data, const size_t data_length, uint8_t* digest);
int MD5_init(MD5_context* ctx);
int MD5_update(MD5_context* ctx, const uint8_t* data, const size_t data_size);
int MD5_transform(MD5_context* ctx, const uint8_t);
int MD5_finalize(uint8_t* digest, MD5_context* ctx);

#endif
