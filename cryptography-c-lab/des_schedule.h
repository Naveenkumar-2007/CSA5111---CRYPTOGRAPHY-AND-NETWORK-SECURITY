#ifndef DES_SCHEDULE_H
#define DES_SCHEDULE_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static const int DES_PC1[56]={57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};
static const int DES_PC2[48]={14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};
static const int DES_SHIFTS[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
static inline uint64_t des_permute(uint64_t in, const int *table, int n, int inbits) { uint64_t out=0; for(int i=0;i<n;++i){ out=(out<<1)|((in>>(inbits-table[i]))&1ULL); } return out; }
static inline void des_make_subkeys(uint64_t key, uint64_t ks[16], uint32_t cs[17], uint32_t ds[17]) { uint64_t k=des_permute(key,DES_PC1,56,64); uint32_t c=(uint32_t)((k>>28)&0x0fffffff), d=(uint32_t)(k&0x0fffffff); cs[0]=c; ds[0]=d; for(int r=0;r<16;++r){int s=DES_SHIFTS[r]; c=((c<<s)|(c>>(28-s)))&0x0fffffff; d=((d<<s)|(d>>(28-s)))&0x0fffffff; cs[r+1]=c; ds[r+1]=d; ks[r]=des_permute(((uint64_t)c<<28)|d,DES_PC2,48,56);} }
static inline int des_parse_hex64(const char *s, uint64_t *v) { char *end=NULL; unsigned long long x=strtoull(s,&end,16); if(!s[0]||!end||*end!='\0') return 0; *v=(uint64_t)x; return 1; }
#endif
