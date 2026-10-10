#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define OPENSSL_SUPPRESS_DEPRECATED
#include <openssl/des.h>
static int hexkey(const char*s,DES_cblock*k){if(strlen(s)!=16)return 0;for(int i=0;i<8;i++){unsigned int v;if(sscanf(s+2*i,"%2x",&v)!=1)return 0;(*k)[i]=(unsigned char)v;}return 1;}
int main(void){char keyhex[32],text[256];DES_cblock key,in,out,back;DES_key_schedule ks;printf("DES key as 16 hex digits (example 133457799BBCDFF1): ");if(scanf("%31s",keyhex)!=1||!hexkey(keyhex,&key)){puts("Invalid key.");return 1;}getchar();printf("Enter plaintext (up to 8 bytes; zero-padded for this one-block demo): ");if(!fgets(text,sizeof text,stdin))return 1;memset(in,0,8);memcpy(in,text,strlen(text)<8?strlen(text):8);DES_set_key_unchecked(&key,&ks);DES_ecb_encrypt(&in,&out,&ks,DES_ENCRYPT);printf("Ciphertext hex: ");for(int i=0;i<8;i++)printf("%02X",out[i]);DES_ecb_encrypt(&out,&back,&ks,DES_DECRYPT);printf("\nRecovered bytes: ");for(int i=0;i<8;i++){if(back[i]>=32&&back[i]<=126)putchar(back[i]);else printf("\\x%02X",back[i]);}puts("\nWARNING: DES is obsolete and insecure. This is for lab learning only; use a modern authenticated cipher in real systems.");return 0;}
