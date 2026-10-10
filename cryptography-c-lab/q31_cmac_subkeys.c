#include <stdio.h>
#include <stdint.h>
#include <string.h>
static int shift_left(uint8_t *a,int n){int carry=0;for(int i=n-1;i>=0;i--){int next=(a[i]>>7)&1;a[i]=(uint8_t)((a[i]<<1)|carry);carry=next;}return carry;}
static void derive(const uint8_t *L,int n,uint8_t rb,uint8_t *k1,uint8_t *k2){memcpy(k1,L,(size_t)n);int carry=shift_left(k1,n);if(carry)k1[n-1]^=rb;memcpy(k2,k1,(size_t)n);carry=shift_left(k2,n);if(carry)k2[n-1]^=rb;}
int main(void){uint8_t L128[16],k1[16],k2[16];for(int i=0;i<16;i++)L128[i]=(uint8_t)(i*17+3);derive(L128,16,0x87,k1,k2);puts("CMAC constants: Rb=0x1B for a 64-bit block; Rb=0x87 for a 128-bit block.");printf("Example input L=AES_K(0^128): ");for(int i=0;i<16;i++)printf("%02X",L128[i]);printf("\nK1: ");for(int i=0;i<16;i++)printf("%02X",k1[i]);printf("\nK2: ");for(int i=0;i<16;i++)printf("%02X",k2[i]);puts("");puts("Left shift implements multiplication by x in GF(2^n); if the original MSB was 1, XOR Rb reduces modulo the block-size-specific polynomial.");return 0;}
