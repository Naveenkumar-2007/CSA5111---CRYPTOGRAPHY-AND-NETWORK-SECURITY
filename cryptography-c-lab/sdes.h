#ifndef SDES_H
#define SDES_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
static inline int sd_permute(int x,const int *tab,int n,int inbits){int out=0;for(int i=0;i<n;i++)out=(out<<1)|((x>>(inbits-tab[i]))&1);return out;}
static inline void sd_keys(int key,int *k1,int *k2){static const int p10[10]={3,5,2,7,4,10,1,9,8,6},p8[8]={6,3,7,4,8,5,10,9};int x=sd_permute(key,p10,10,10),l=(x>>5)&31,r=x&31;l=((l<<1)|(l>>4))&31;r=((r<<1)|(r>>4))&31;*k1=sd_permute((l<<5)|r,p8,8,10);l=(((l<<2)|(l>>3))&31);r=(((r<<2)|(r>>3))&31);*k2=sd_permute((l<<5)|r,p8,8,10);}
static inline int sd_fk(int x,int key){static const int ep[8]={4,1,2,3,2,3,4,1},p4[4]={2,4,3,1};static const int s0[4][4]={{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}};static const int s1[4][4]={{0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3}};int l=(x>>4)&15,r=x&15,ex=sd_permute(r,ep,8,4)^key;int a=(ex>>4)&15,b=ex&15;int row=((a&8)>>2)|(a&1),col=(a>>1)&3;int v0=s0[row][col];row=((b&8)>>2)|(b&1);col=(b>>1)&3;int v1=s1[row][col];int sp=sd_permute((v0<<2)|v1,p4,4,4);return (((l^sp)&15)<<4)|r;}
static inline int sd_encrypt(int p,int key){static const int ip[8]={2,6,3,1,4,8,5,7},ip1[8]={4,1,3,5,7,2,8,6};int k1,k2;sd_keys(key,&k1,&k2);int x=sd_permute(p,ip,8,8);x=sd_fk(x,k1);x=((x&15)<<4)|((x>>4)&15);x=sd_fk(x,k2);return sd_permute(x,ip1,8,8);}
static inline int sd_decrypt(int c,int key){static const int ip[8]={2,6,3,1,4,8,5,7},ip1[8]={4,1,3,5,7,2,8,6};int k1,k2;sd_keys(key,&k1,&k2);int x=sd_permute(c,ip,8,8);x=sd_fk(x,k2);x=((x&15)<<4)|((x>>4)&15);x=sd_fk(x,k1);return sd_permute(x,ip1,8,8);}
static inline int sd_parse_bits(const char*s,int n,int *value){int x=0,c=0;for(int i=0;s[i];i++){if(s[i]=='0'||s[i]=='1'){x=(x<<1)|(s[i]-'0');c++;}}if(c!=n)return 0;*value=x;return 1;}
#endif
