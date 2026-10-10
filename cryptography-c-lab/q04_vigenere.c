#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char key[256], text[2048], mode;
    printf("Enter alphabetic key: ");
    if (scanf("%255s", key) != 1) return 1;
    size_t key_len = 0;
    for (size_t i = 0; key[i]; ++i) if (isalpha((unsigned char)key[i])) key[key_len++] = (char)toupper((unsigned char)key[i]);
    key[key_len] = '\0';
    if (key_len == 0) { puts("Key must contain letters."); return 1; }
    printf("Encrypt (E) or Decrypt (D)? ");
    if (scanf(" %c", &mode) != 1) return 1;
    mode = (char)toupper((unsigned char)mode);
    if (mode != 'E' && mode != 'D') { puts("Enter E or D."); return 1; }
    getchar();
    printf("Enter message: ");
    if (!fgets(text, sizeof text, stdin)) return 1;
    size_t j = 0;
    for (size_t i = 0; text[i]; ++i) {
        unsigned char c = (unsigned char)text[i];
        if (c >= 'A' && c <= 'Z') {
            int shift = key[j % key_len] - 'A';
            text[i] = (char)('A' + ((c - 'A' + (mode == 'E' ? shift : 26 - shift)) % 26)); ++j;
        } else if (c >= 'a' && c <= 'z') {
            int shift = key[j % key_len] - 'A';
            text[i] = (char)('a' + ((c - 'a' + (mode == 'E' ? shift : 26 - shift)) % 26)); ++j;
        }
    }
    printf("Result: %s", text);
    return 0;
}
