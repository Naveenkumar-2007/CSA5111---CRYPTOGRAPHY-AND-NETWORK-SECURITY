#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char keyword[256], text[2048], mode;
    char cipher[27]; int seen[26] = {0}; int n = 0;
    printf("Enter keyword (example CIPHER): ");
    if (scanf("%255s", keyword) != 1) return 1;
    for (size_t i = 0; keyword[i]; ++i) {
        unsigned char c = (unsigned char)toupper((unsigned char)keyword[i]);
        if (c >= 'A' && c <= 'Z' && !seen[c - 'A']) { cipher[n++] = (char)c; seen[c - 'A'] = 1; }
    }
    for (char c = 'A'; c <= 'Z'; ++c) if (!seen[c - 'A']) cipher[n++] = c;
    cipher[26] = '\0';
    puts("\nPlain : ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    printf("Cipher: %s\n", cipher);
    printf("Encrypt (E) or Decrypt (D)? ");
    if (scanf(" %c", &mode) != 1) return 1;
    mode = (char)toupper((unsigned char)mode);
    if (mode != 'E' && mode != 'D') { puts("Enter E or D."); return 1; }
    getchar();
    printf("Enter message: ");
    if (!fgets(text, sizeof text, stdin)) return 1;
    for (size_t i = 0; text[i]; ++i) {
        unsigned char c = (unsigned char)text[i];
        if (c >= 'A' && c <= 'Z') {
            int idx = c - 'A';
            if (mode == 'E') text[i] = cipher[idx];
            else for (int j = 0; j < 26; ++j) if (cipher[j] == c) { text[i] = (char)('A' + j); break; }
        } else if (c >= 'a' && c <= 'z') {
            int idx = c - 'a';
            if (mode == 'E') text[i] = (char)tolower((unsigned char)cipher[idx]);
            else for (int j = 0; j < 26; ++j) if (cipher[j] == toupper(c)) { text[i] = (char)('a' + j); break; }
        }
    }
    printf("Result: %s", text);
    return 0;
}
