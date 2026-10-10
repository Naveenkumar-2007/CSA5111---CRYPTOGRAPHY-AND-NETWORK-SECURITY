#ifndef CRYPTOUTILS_H
#define CRYPTOUTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

static inline int cu_mod(int x, int m) { int r = x % m; return r < 0 ? r + m : r; }
static inline int cu_gcd(int a, int b) { while (b) { int t = b; b = a % b; a = t; } return a < 0 ? -a : a; }
static inline int cu_inv(int a, int m) { a = cu_mod(a,m); for (int x=1; x<m; ++x) if ((a*x)%m==1) return x; return -1; }
static inline unsigned long long cu_modpow(unsigned long long a, unsigned long long e, unsigned long long m) { unsigned long long r=1; a%=m; while(e){ if(e&1) r=(r*a)%m; a=(a*a)%m; e>>=1;} return r; }
static inline void cu_letters(const char *src, char *dst, int merge_j) { size_t n=0; for(size_t i=0;src[i];++i) { unsigned char c=(unsigned char)toupper((unsigned char)src[i]); if(c>='A'&&c<='Z'){ if(merge_j&&c=='J') c='I'; dst[n++]=(char)c; }} dst[n]='\0'; }
static inline void cu_readline(const char *prompt, char *buf, size_t n) { fputs(prompt,stdout); if(!fgets(buf,(int)n,stdin)) buf[0]='\0'; buf[strcspn(buf,"\r\n")]='\0'; }
static inline void cu_print_bits(unsigned int x, int n) { for(int i=n-1;i>=0;--i) putchar((x>>i)&1?'1':'0'); }
#endif
