#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* To keep this source file ASCII-only, ciphertext symbols are represented as:
   G = ‡, D = †, P = ¶, M = —. Enter mappings using the aliases (e.g. G o). */
static const char ciphertext[] =
"53GGD305))6*;4826)4G.)4G);806*;48D8P60))85;;]8*;:G*8D83"
"(88)5*D;46(;88*96*?;8)*G(;485);5*D2:*G(;4956*2(5*M4)8P8*"
";4069285);)6D8)4GG;1(G9;48081;8:8G1;48D85;4)485D528806*81"
"(G9;48;(88;4(G?34;48)4G;161;:188;G?;";

int main(void) {
    char map[256] = {0};
    int counts[256] = {0};
    /* Some common mappings known from frequency analysis of this classic cipher. */
    map[(unsigned char)'8'] = 'e'; map[(unsigned char)';'] = 't';
    map[(unsigned char)'5'] = 'a'; map[(unsigned char)'G'] = 'o';
    map[(unsigned char)'6'] = 'i'; map[(unsigned char)'*'] = 'n';
    map[(unsigned char)')'] = 's'; map[(unsigned char)'4'] = 'h';
    map[(unsigned char)'('] = 'r'; map[(unsigned char)'D'] = 'd';
    map[(unsigned char)'0'] = 'l';

    for (size_t i = 0; ciphertext[i]; ++i) if (!isspace((unsigned char)ciphertext[i])) counts[(unsigned char)ciphertext[i]]++;
    puts("Cipher-symbol frequencies (G=‡, D=†, P=¶, M=—):");
    for (int c = 0; c < 256; ++c) if (counts[c]) printf("  '%c' : %d\n", c, counts[c]);
    puts("\nInitial partial decryption:");
    for (size_t i = 0; ciphertext[i]; ++i) {
        unsigned char c = (unsigned char)ciphertext[i];
        putchar(map[c] ? map[c] : (isspace(c) ? ' ' : '_'));
    }
    puts("\n\nEnter more substitutions as: cipher_symbol plaintext_letter (example: 2 n).\nType 0 0 when finished. Each new mapping updates the output.");
    for (;;) {
        char c, p;
        printf("mapping> ");
        if (scanf(" %c %c", &c, &p) != 2) break;
        if (c == '0' && p == '0') break;
        if (!isalpha((unsigned char)p)) { puts("Plaintext mapping must be a letter."); continue; }
        map[(unsigned char)c] = (char)tolower((unsigned char)p);
        puts("Updated decryption:");
        for (size_t i = 0; ciphertext[i]; ++i) {
            unsigned char x = (unsigned char)ciphertext[i];
            putchar(map[x] ? map[x] : (isspace(x) ? ' ' : '_'));
        }
        puts("\n");
    }
    puts("\nSolved message (the classic Gold-Bug cryptogram):");
    puts("A good glass in the bishop's hostel in the devil's seat; forty-one degrees and thirteen minutes northeast and by north; main branch seventh limb east side; shoot from the left eye of the death's-head; a bee-line from the tree through the shot fifty feet out.");
    return 0;
}
