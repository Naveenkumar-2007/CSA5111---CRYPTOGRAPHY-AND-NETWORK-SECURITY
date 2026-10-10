#include <stdio.h>
#include <string.h>
#include <ctype.h>

static int valid_key(const char *key) {
    int seen[26] = {0};
    if (strlen(key) != 26) return 0;
    for (int i = 0; i < 26; ++i) {
        unsigned char c = (unsigned char)toupper((unsigned char)key[i]);
        if (c < 'A' || c > 'Z' || seen[c - 'A']) return 0;
        seen[c - 'A'] = 1;
    }
    return 1;
}

int main(void) {
    char key[128], text[2048], mode;
    printf("Enter a 26-letter substitution alphabet (cipher for A through Z): ");
    if (scanf("%127s", key) != 1) return 1;
    if (!valid_key(key)) {
        puts("Invalid key: use each English letter exactly once.");
        return 1;
    }
    for (int i = 0; i < 26; ++i) key[i] = (char)toupper((unsigned char)key[i]);
    printf("Encrypt (E) or Decrypt (D)? ");
    if (scanf(" %c", &mode) != 1) return 1;
    mode = (char)toupper((unsigned char)mode);
    if (mode != 'E' && mode != 'D') { puts("Enter E or D."); return 1; }
    getchar();
    printf("Enter message: ");
    if (!fgets(text, sizeof text, stdin)) return 1;

    for (size_t i = 0; text[i] != '\0'; ++i) {
        unsigned char c = (unsigned char)text[i];
        if (isalpha(c) && c < 128) {
            int idx = toupper(c) - 'A';
            char out = mode == 'E' ? key[idx] : (char)('A' + idx);
            if (mode == 'D') {
                for (int j = 0; j < 26; ++j) if (key[j] == toupper(c)) { out = (char)('A' + j); break; }
            }
            text[i] = islower(c) ? (char)tolower((unsigned char)out) : out;
        }
    }
    printf("Result: %s", text);
    return 0;
}
