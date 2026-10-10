#include <stdio.h>
#include <string.h>
#include <ctype.h>

static void build_square(const char *key, char square[25]) {
    int seen[26] = {0}, n = 0;
    for (size_t i = 0; key[i]; ++i) {
        unsigned char c = (unsigned char)toupper((unsigned char)key[i]);
        if (c < 'A' || c > 'Z') continue;
        if (c == 'J') c = 'I';
        if (!seen[c - 'A']) { square[n++] = (char)c; seen[c - 'A'] = 1; }
    }
    for (char c = 'A'; c <= 'Z'; ++c) if (c != 'J' && !seen[c - 'A']) square[n++] = c;
}
static int position(const char square[25], char c) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < 25; ++i) if (square[i] == c) return i;
    return -1;
}
static void decrypt_pair(const char square[25], char *a, char *b) {
    int p1 = position(square, *a), p2 = position(square, *b);
    int r1 = p1 / 5, c1 = p1 % 5, r2 = p2 / 5, c2 = p2 % 5;
    if (r1 == r2) { c1 = (c1 + 4) % 5; c2 = (c2 + 4) % 5; }
    else if (c1 == c2) { r1 = (r1 + 4) % 5; r2 = (r2 + 4) % 5; }
    else { int t = c1; c1 = c2; c2 = t; }
    *a = square[r1 * 5 + c1]; *b = square[r2 * 5 + c2];
}
int main(void) {
    const char *key = "royal new zealand navy";
    const char *ciphertext =
        "KXJEYUREBEZWEHEWRYTUHEYFS"
        "KREHEGOYFIWTTTUOLKSYCAJPO"
        "BOTEIZONTXBYBNTGONEYCUZWR"
        "GDSONSXBOUYWRHEBAAHYUSEDQ";
    char square[25], plain[256]; size_t n = 0;
    build_square(key, square);
    puts("Playfair square for key: royal new zealand navy");
    for (int i = 0; i < 25; ++i) printf("%c%c", square[i], i % 5 == 4 ? '\n' : ' ');
    for (size_t i = 0; ciphertext[i]; ++i) {
        unsigned char c = (unsigned char)ciphertext[i];
        if (isalpha(c) && n + 1 < sizeof plain) plain[n++] = (char)toupper(c);
    }
    if (n % 2 != 0) { puts("Ciphertext length must be even."); return 1; }
    for (size_t i = 0; i + 1 < n; i += 2) {
        /* The textbook explicitly says to translate the repeated ciphertext pair TT as plaintext tt. */
        if (plain[i] == 'T' && plain[i + 1] == 'T') { plain[i] = 't'; plain[i + 1] = 't'; }
        else decrypt_pair(square, &plain[i], &plain[i + 1]);
    }
    plain[n] = '\0';
    printf("\nDecrypted letters (grouped in digraphs):\n");
    for (size_t i = 0; i < n; ++i) { putchar(plain[i]); if (i % 2 == 1) putchar(' '); if ((i + 1) % 10 == 0) putchar(' '); }
    printf("\n\nJoin the letters to read them as a message:\n");
    for (size_t i = 0; i < n; ++i) putchar(plain[i]);
    puts("\n\nInsert word spaces by context. The assignment explicitly says to interpret ciphertext TT as plaintext tt.");
    return 0;
}
