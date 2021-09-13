#include"MD5.h"
#include<string.h>

/* FOUR NON-LINEAR FUNCTIONS 
   ROUND_F BIT-WISE CONDITIONAL
   ROUND-H BIT-WISE PARITY OPERATOR */

static inline uint32_t ROUND_F(uint32_t X,uint32_t Y,uint32_t Z){
    return ((X & Y) | ((~X) & Z));
}
static inline uint32_t ROUND_G(uint32_t X,uint32_t Y,uint32_t Z){
    return ((X & Z) ~ (Y | (~Z));
}
static inline uint32_t ROUND_H(uint32_t X,uint32_t Y,uint32_t Z){
    return (X ^ Y ^ Z);
}
static inline uint32_t ROUND_I(uint32_t X,uint32_t Y,uint32_t Z){
    return ((Y) ^ (X | (~Z));
}   
/* CIRCULAR LEFT SHIFT */
static inline uint32_t CIRCULAR_LEFT_SHIFT(uint32_t X,uint8_t N_BITS){
    return (((X) << (N_BITS)) | (X) >> (32-N_BITS));
}


/* SUB-BLOCK J=0...15 FOUR OPERATIONS 16 x 4 -> 16 rounds each bloack*/
const uint32_t CONSTANT_ADDITIVE[16][4] = {
	0xd76aa478,0xf61e2562,0xfffa3942,0xf4292244,
	0xe8c7b756,0xc040b340,0x8771f681,0x432aff97,
	0x242070db,0x265e5a51,0x6d9d6122,0xab9423a7,
	0xc1bdceee,0xe9b6c7aa,0xfde5380c,0xfc93a039,
	0xf57c0faf,0xd62f105d,0xa4beea44,0x655b59c3,
	0x4787c62a,0x02441453,0x4bdecfa9,0x8f0ccc92,
	0xa8304613,0xd8a1e681,0xf6bb4b60,0xffeff47d,
	0xfd469501,0xe7d3fbc8,0xbebfbc70,0x85845dd1,
	0x698098d8,0x21e1cde6,0x289b7ec6,0x6fa87e4f,
	0x8b44f7af,0xc33707d6,0xeaa127fa,0xfe2ce6e0,
	0xffff5bb1,0xf4d50d87,0xd4ef3085,0xa3014314,
	0x895cd7be,0x455a14ed,0x04881d05,0x4e0811a1,
	0x6b901122,0xa9e3e905,0xd9d4d039,0xf7537e82,
	0xfd987193,0xfcefa3f8,0xe6db99e5,0xbd3af235,
	0xa679438e,0x676f02d9,0x1fa27cf8,0x2ad7d2bb,
	0x49b40821,0x8d2a4c8a,0xc4ac5665,0xeb86d391
};

/* ROUND_FF 16 SUB_ROUNDS  AND CONSTANTS */
#define ROUND_FF_SHIFT_CONSTANT_1 7
#define ROUND_FF_SHIFT_CONSTANT_2 12
#define ROUND_FF_SHIFT_CONSTANT_3 17
#define ROUND_FF_SHIFT_CONSTANT_4 22

static inline void ROUND_FF(uint32_t* state_a, 
                            uint32_t state_b,
                            uint32_t state_c,
                            uint32_t state_d,
                            uint32_t jth_sub_block,
                            uint8_t n_circular_left_shift,
                            uint32_t current_round_constant){
    /* a = b + ((a + F(b,c,d) + M_jth + t_ith) <<< s)*/                          
    uint32_t sum = *state_a + ROUND_F(state_b, state_c, state_d);
             sum += jth_sub_block + current_round_constant; 
    *state_a = state_b + CIRCULAR_LEFT_SHIFT(sum, n_circular_left_shift);
}
/* ROUND_GG 16 SUB_ROUNDS AND CONSTANTS */
#define ROUND_GG_SHIFT_CONSTANT_1 5
#define ROUND_GG_SHIFT_CONSTANT_2 9
#define ROUND_GG_SHIFT_CONSTANT_3 14
#define ROUND_GG_SHIFT_CONSTANT_4 20

static inline void ROUND_GG(uint32_t* state_a, 
                            uint32_t state_b,
                            uint32_t state_c,
                            uint32_t state_d,
                            uint32_t jth_sub_block,
                            uint8_t n_circular_left_shift,
                            uint32_t current_round_constant){
    /* a = b + ((a + G(b,c,d) + M_jth + t_ith) <<< s)*/                          
    uint32_t sum = *state_a + ROUND_G(state_b, state_c, state_d);
             sum += jth_sub_block + current_round_constant; 
    *state_a = state_b + CIRCULAR_LEFT_SHIFT(sum, n_circular_left_shift);
}
/* ROUND_HH 16 SUB_ROUNDS */
#define ROUND_HH_SHIFT_CONSTANT_1 4
#define ROUND_HH_SHIFT_CONSTANT_2 11
#define ROUND_HH_SHIFT_CONSTANT_3 16
#define ROUND_HH_SHIFT_CONSTANT_4 23

static inline void ROUND_HH(uint32_t* state_a, 
                            uint32_t state_b,
                            uint32_t state_c,
                            uint32_t state_d,
                            uint32_t jth_sub_block,
                            uint8_t n_circular_left_shift,
                            uint32_t current_round_constant){
    /* a = b + ((a + H(b,c,d) + M_jth + t_ith) <<< s)*/                          
    uint32_t sum = *state_a + ROUND_H(state_b, state_c, state_d);
             sum += jth_sub_block + current_round_constant; 
    *state_a = state_b + CIRCULAR_LEFT_SHIFT(sum, n_circular_left_shift);
}
/* ROUND_II 16 SUB_ROUNDS */
#define ROUND_II_SHIFT_CONSTANT_1 6
#define ROUND_II_SHIFT_CONSTANT_2 10
#define ROUND_II_SHIFT_CONSTANT_3 15
#define ROUND_II_SHIFT_CONSTANT_4 21

static inline void ROUND_II(uint32_t* state_a, 
                            uint32_t state_b,
                            uint32_t state_c,
                            uint32_t state_d,
                            uint32_t jth_sub_block,
                            uint8_t n_circular_left_shift,
                            uint32_t current_round_constant){
    /* a = b + ((a + F(b,c,d) + M_jth + t_ith) <<< s)*/                          
    uint32_t sum = *state_a + ROUND_I(state_b, state_c, state_d);
             sum += jth_sub_block + current_round_constant; 
    *state_a = state_b + CIRCULAR_LEFT_SHIFT(sum, n_circular_left_shift);
}

#define MD5_DIGEST_SIZE 16 /* Bytes */
#define BLOCK_SIZE 64 /* Bytes */

uint8_t* MD5_digest(const uint8_t* data, const size_t data_length, uint8_t digest[MD5_DIGEST_SIZE]){

    MD5_context md5_ctx; /* Create MD5 Instance */
    MD5_init(&md5_ctx); /* Initialize MD5 Instance */
    MD5_update(&md5_ctx); /* Compute MD5 Hash */
    MD5_finalize(&md5_ctx); /* Finalize MD5 Hash */
    
    return digest; /* returns Digest */

}
int MD5_init(MD5_context* ctx){

    /* Zeros initialize */
    memset(&ctx, 0, sizeof(*ctx));
    /* Chaining Variables */
    ctx->state[0] = (uint32_t)0x67452301; /* A */
        ctx->state[1] = (uint32_t)0xefcdab89; /* B */
            ctx->state[2] = (uint32_t)0x98badcfe; /* C */
                ctx->state[3] = (uint32_t)0x10325476; /* D */
                
     return 1; /* returns Success */
}
int MD5_update(MD5_context* ctx, const uint8_t* data, const size_t data_size){


}
int MD5_transform(MD5_context* ctx, const uint32_t* data){
    uint32_t a  = ctx->state[0]; 
    uint32_t b  = ctx->state[1]; 
    uint32_t c  = ctx->state[2]; 
    uint32_t d  = ctx->state[3];
    

    
    /* 16 SUB_ROUND COMPUTATION */
    
    /* ROUND FF */
    ROUND_FF(&a,b,c,d,data[0],ROUND_FF_SHIFT_CONSTANT_1,CONSTANT_ADDITIVE[0][0]);
        ROUND_FF(&d,a,b,c,data[1],ROUND_FF_SHIFT_CONSTANT_2,CONSTANT_ADDITIVE[1][0]);
            ROUND_FF(&c,d,a,b,data[2],ROUND_FF_SHIFT_CONSTANT_3,CONSTANT_ADDITIVE[2][0]);
                ROUND_FF(&b,c,d,c,data[3],ROUND_FF_SHIFT_CONSTANT_4,CONSTANT_ADDITIVE[3][0]);
    ROUND_FF(&a,b,c,d,data[4],ROUND_FF_SHIFT_CONSTANT_1,CONSTANT_ADDITIVE[4][0]);
        ROUND_FF(&d,a,b,c,data[5],ROUND_FF_SHIFT_CONSTANT_2,CONSTANT_ADDITIVE[5][0]);
            ROUND_FF(&c,d,a,b,data[6],ROUND_FF_SHIFT_CONSTANT_3,CONSTANT_ADDITIVE[6][0]);
                ROUND_FF(&b,c,d,c,data[7],ROUND_FF_SHIFT_CONSTANT_4,CONSTANT_ADDITIVE[7][0]);
    ROUND_FF(&a,b,c,d,data[8],ROUND_FF_SHIFT_CONSTANT_1,CONSTANT_ADDITIVE[8][0]);
        ROUND_FF(&d,a,b,c,data[9],ROUND_FF_SHIFT_CONSTANT_2,CONSTANT_ADDITIVE[9][0]);
            ROUND_FF(&c,d,a,b,data[10],ROUND_FF_SHIFT_CONSTANT_3,CONSTANT_ADDITIVE[10][0]);
                ROUND_FF(&b,c,d,c,data[11],ROUND_FF_SHIFT_CONSTANT_4,CONSTANT_ADDITIVE[11][0]);
    ROUND_FF(&a,b,c,d,data[12],ROUND_FF_SHIFT_CONSTANT_1,CONSTANT_ADDITIVE[12][0]);
        ROUND_FF(&d,a,b,c,data[13],ROUND_FF_SHIFT_CONSTANT_2,CONSTANT_ADDITIVE[13][0]);
            ROUND_FF(&c,d,a,b,data[14],ROUND_FF_SHIFT_CONSTANT_3,CONSTANT_ADDITIVE[14][0]);
                ROUND_FF(&b,c,d,c,data[15],ROUND_FF_SHIFT_CONSTANT_4,CONSTANT_ADDITIVE[15][0]);
                
    /* ROUND GG */
    ROUND_GG(&a,b,c,d,data[1],ROUND_GG_SHIFT_CONSTANT_1,CONSTANT_ADDITIVE[0][1]);
        ROUND_GG(&d,a,b,c,data[6],ROUND_GG_SHIFT_CONSTANT_2,CONSTANT_ADDITIVE[1][1]);
            ROUND_GG(&c,d,a,b,data[11],ROUND_GG_SHIFT_CONSTANT_3,CONSTANT_ADDITIVE[2][1]);
                ROUND_GG(&b,c,d,c,data[0],ROUND_GG_SHIFT_CONSTANT_4,CONSTANT_ADDITIVE[3][1]);
    ROUND_GG(&a,b,c,d,data[5],ROUND_GG_SHIFT_CONSTANT_1,CONSTANT_ADDITIVE[4][1]);
        ROUND_GG(&d,a,b,c,data[10],ROUND_GG_SHIFT_CONSTANT_2,CONSTANT_ADDITIVE[5][1]);
            ROUND_GG(&c,d,a,b,data[15],ROUND_GG_SHIFT_CONSTANT_3,CONSTANT_ADDITIVE[6][1]);
                ROUND_GG(&b,c,d,c,data[4],ROUND_GG_SHIFT_CONSTANT_4,CONSTANT_ADDITIVE[7][1]);
    ROUND_GG(&a,b,c,d,data[9],ROUND_GG_SHIFT_CONSTANT_1,CONSTANT_ADDITIVE[8][1]);
        ROUND_GG(&d,a,b,c,data[14],ROUND_GG_SHIFT_CONSTANT_2,CONSTANT_ADDITIVE[9][1]);
            ROUND_GG(&c,d,a,b,data[3],ROUND_GG_SHIFT_CONSTANT_3,CONSTANT_ADDITIVE[10][1]);
                ROUND_GG(&b,c,d,c,data[8],ROUND_GG_SHIFT_CONSTANT_4,CONSTANT_ADDITIVE[11][1]);
    ROUND_GG(&a,b,c,d,data[13],ROUND_GG_SHIFT_CONSTANT_1,CONSTANT_ADDITIVE[12][1]);
        ROUND_GG(&d,a,b,c,data[2],ROUND_GG_SHIFT_CONSTANT_2,CONSTANT_ADDITIVE[13][1]);
            ROUND_GG(&c,d,a,b,data[7],ROUND_GG_SHIFT_CONSTANT_3,CONSTANT_ADDITIVE[14][1]);
                ROUND_GG(&b,c,d,c,data[12],ROUND_GG_SHIFT_CONSTANT_4,CONSTANT_ADDITIVE[15][1]);
    /* ROUND HH */
    ROUND_HH(&a,b,c,d,data[1],ROUND_HH_SHIFT_CONSTANT_1,CONSTANT_ADDITIVE[0][2]);
        ROUND_HH(&d,a,b,c,data[6],ROUND_HH_SHIFT_CONSTANT_2,CONSTANT_ADDITIVE[1][2]);
            ROUND_HH(&c,d,a,b,data[11],ROUND_HH_SHIFT_CONSTANT_3,CONSTANT_ADDITIVE[2][2]);
                ROUND_HH(&b,c,d,c,data[0],ROUND_HH_SHIFT_CONSTANT_4,CONSTANT_ADDITIVE[3][2]);
    ROUND_HH(&a,b,c,d,data[5],ROUND_HH_SHIFT_CONSTANT_1,CONSTANT_ADDITIVE[4][2]);
        ROUND_HH(&d,a,b,c,data[10],ROUND_HH_SHIFT_CONSTANT_2,CONSTANT_ADDITIVE[5][2]);
            ROUND_HH(&c,d,a,b,data[15],ROUND_HH_SHIFT_CONSTANT_3,CONSTANT_ADDITIVE[6][2]);
                ROUND_HH(&b,c,d,c,data[4],ROUND_HH_SHIFT_CONSTANT_4,CONSTANT_ADDITIVE[7][2]);
    ROUND_HH(&a,b,c,d,data[9],ROUND_HH_SHIFT_CONSTANT_1,CONSTANT_ADDITIVE[8][2]);
        ROUND_HH(&d,a,b,c,data[14],ROUND_HH_SHIFT_CONSTANT_2,CONSTANT_ADDITIVE[9][2]);
            ROUND_HH(&c,d,a,b,data[3],ROUND_HH_SHIFT_CONSTANT_3,CONSTANT_ADDITIVE[10][2]);
                ROUND_HH(&b,c,d,c,data[8],ROUND_HH_SHIFT_CONSTANT_4,CONSTANT_ADDITIVE[11][2]);
    ROUND_HH(&a,b,c,d,data[13],ROUND_GG_SHIFT_CONSTANT_1,CONSTANT_ADDITIVE[12][2]);
        ROUND_HH(&d,a,b,c,data[2],ROUND_GG_SHIFT_CONSTANT_2,CONSTANT_ADDITIVE[13][2]);
            ROUND_HH(&c,d,a,b,data[7],ROUND_GG_SHIFT_CONSTANT_3,CONSTANT_ADDITIVE[14][2]);
                ROUND_HH(&b,c,d,c,data[12],ROUND_GG_SHIFT_CONSTANT_4,CONSTANT_ADDITIVE[15][2]); 
    /* ROUND II */
    ROUND_II(&a,b,c,d,data[1],ROUND_II_SHIFT_CONSTANT_1,CONSTANT_ADDITIVE[0][3]);
        ROUND_II(&d,a,b,c,data[6],ROUND_II_SHIFT_CONSTANT_2,CONSTANT_ADDITIVE[1][3]);
            ROUND_II(&c,d,a,b,data[11],ROUND_II_SHIFT_CONSTANT_3,CONSTANT_ADDITIVE[2][3]);
                ROUND_II(&b,c,d,c,data[0],ROUND_II_SHIFT_CONSTANT_4,CONSTANT_ADDITIVE[3][3]);
    ROUND_II(&a,b,c,d,data[5],ROUND_II_SHIFT_CONSTANT_1,CONSTANT_ADDITIVE[4][3]);
        ROUND_II(&d,a,b,c,data[10],ROUND_II_SHIFT_CONSTANT_2,CONSTANT_ADDITIVE[5][3]);
            ROUND_II(&c,d,a,b,data[15],ROUND_II_SHIFT_CONSTANT_3,CONSTANT_ADDITIVE[6][3]);
                ROUND_II(&b,c,d,c,data[4],ROUND_II_SHIFT_CONSTANT_4,CONSTANT_ADDITIVE[7][3]);
    ROUND_II(&a,b,c,d,data[9],ROUND_II_SHIFT_CONSTANT_1,CONSTANT_ADDITIVE[8][3]);
        ROUND_II(&d,a,b,c,data[14],ROUND_II_SHIFT_CONSTANT_2,CONSTANT_ADDITIVE[9][3]);
            ROUND_II(&c,d,a,b,data[3],ROUND_II_SHIFT_CONSTANT_3,CONSTANT_ADDITIVE[10][3]);
                ROUND_II(&b,c,d,c,data[8],ROUND_II_SHIFT_CONSTANT_4,CONSTANT_ADDITIVE[11][3]);
    ROUND_II(&a,b,c,d,data[13],ROUND_II_SHIFT_CONSTANT_1,CONSTANT_ADDITIVE[12][3]);
        ROUND_II(&d,a,b,c,data[2],ROUND_II_SHIFT_CONSTANT_2,CONSTANT_ADDITIVE[13][3]);
            ROUND_II(&c,d,a,b,data[7],ROUND_II_SHIFT_CONSTANT_3,CONSTANT_ADDITIVE[14][3]);
                ROUND_II(&b,c,d,c,data[12],ROUND_II_SHIFT_CONSTANT_4,CONSTANT_ADDITIVE[15][3]);
                

    ctx->state[0] += a;
        ctx->state[1] += b;
            ctx->state[2] += c;
                ctx->state[3] += d;
}
int MD5_finalize(uint8_t* digest, MD5_context* ctx){

}

