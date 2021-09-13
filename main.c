#include<stdio.h>
#include<stdint.h>
#define BYTES_SIZE 4


void encode_print(uint8_t*, uint32_t*);
void decode_print(uint32_t*, uint8_t*);

int main(void){

    uint8_t bytes[BYTES_SIZE];
    uint32_t value = 0x12345678;
    encode_print(bytes, &value);
    decode_print(&value, bytes);
 
    return 0;

}
void encode_print(uint8_t* bytes, uint32_t* integer){
    bytes[0] = *integer & 0xff;
    bytes[1] = *integer >> 8 & 0xff;
    bytes[2] = *integer >> 16 & 0xff;
    bytes[3] = *integer >> 24 & 0xff;
    
    fprintf(stdout,"Original Value: 0x%X\n", *integer);
    
    fprintf(stdout,"0x%X\n", bytes[0]);
        fprintf(stdout,"0x%X\n", bytes[1]);
            fprintf(stdout,"0x%X\n", bytes[2]);
                fprintf(stdout,"0x%X\n", bytes[3]);
}
void decode_print(uint32_t* integer, uint8_t* bytes){
    *integer = (uint32_t)bytes[3]<<24 | (uint32_t)bytes[2]<<16 | (uint32_t)bytes[1]<<8 | (uint32_t)bytes[0];
    fprintf(stdout,"Original bytes\n");
    fprintf(stdout,"0x%X\n", bytes[0]);
        fprintf(stdout,"0x%X\n", bytes[1]);
            fprintf(stdout,"0x%X\n", bytes[2]);
                fprintf(stdout,"0x%X\n", bytes[3]);
    fprintf(stdout,"Result=0x%X\n", *integer);
    

}
