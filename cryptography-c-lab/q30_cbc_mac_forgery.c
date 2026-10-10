#include <stdio.h>
#include <stdint.h>
static uint8_t toyE(uint8_t x){return (uint8_t)(x*197u+101u);}
static uint8_t mac1(uint8_t x){return toyE(x);}
static uint8_t mac2(uint8_t x,uint8_t y){return toyE((uint8_t)(toyE(x)^y));}
int main(void){uint8_t X=0x53,T=mac1(X),second=(uint8_t)(X^T),forged=mac2(X,second);printf("Toy 8-bit CBC-MAC illustration (not a secure cipher):\nX=0x%02X, T=MAC(K,X)=0x%02X\nConstruct second block X XOR T = 0x%02X\nMAC(K, X || (X XOR T)) = 0x%02X\n",X,T,second,forged);puts("The equality happens because CBC's second input is (X XOR T) XOR T = X, so encrypting it yields E_K(X)=T. This shows why plain CBC-MAC is unsafe for variable-length messages without domain separation/length binding.");return 0;}
