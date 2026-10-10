#include <stdio.h>
#include <string.h>
#include <ctype.h>

static void build_square(const char *key, char square[25]) {
    int seen[26] = {0};
    int n = 0;
    for (size_t i = 0; key[i] != '\0'; ++i) {
        unsigned char c = (unsigned char)toupper((unsigned char)key[i]);
        if (c < 'A' || c > 'Z') continue;
        if (c == 'J') c = 'I';
        if (!seen[c - 'A']) { square[n++] = (char)c; seen[c - 'A'] = 1; }
    }
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (c == 'J') continue;
        if (!seen[c - 'A']) { square[n++] = c; seen[c - 'A'] = 1; }
    }
}

static int position(const char square[25], char c) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < 25; ++i) if (square[i] == c) return i;
    return -1;
}

static void transform_pair(const char square[25], char *a, char *b, int decrypt) {
    int p1 = position(square, *a), p2 = position(square, *b);
    int r1 = p1 / 5, c1 = p1 % 5, r2 = p2 / 5, c2 = p2 % 5;
    if (r1 == r2) {
        c1 = (c1 + (decrypt ? 4 : 1)) % 5;
        c2 = (c2 + (decrypt ? 4 : 1)) % 5;
    } else if (c1 == c2) {
        r1 = (r1 + (decrypt ? 4 : 1)) % 5;
        r2 = (r2 + (decrypt ? 4 : 1)) % 5;
    } else {
        int temp = c1; c1 = c2; c2 = temp;
    }
    *a = square[r1 * 5 + c1];
    *b = square[r2 * 5 + c2];
}

static void prepare_plaintext(const char *input, char *output, size_t cap) {
    char letters[2048]; size_t n = 0;
    for (size_t i = 0; input[i] && n + 1 < sizeof letters; ++i) {
        unsigned char c = (unsigned char)toupper((unsigned char)input[i]);
        if (c >= 'A' && c <= 'Z') { if (c == 'J') c = 'I'; letters[n++] = (char)c; }
    }
    letters[n] = '\0';
    size_t out = 0;
    for (size_t i = 0; i < n && out + 2 < cap;) {
        char a = letters[i];
        if (i + 1 >= n) {
            output[out++] = a; output[out++] = (a == 'X' ? 'Q' : 'X'); ++i;
        } else if (a == letters[i + 1]) {
            output[out++] = a; output[out++] = (a == 'X' ? 'Q' : 'X'); ++i;
        } else {
            output[out++] = a; output[out++] = letters[i + 1]; i += 2;
        }
    }
    output[out] = '\0';
}

int main(void) {
    char key[256], text[2048], prepared[4096], mode;
    char square[25];
    printf("Enter keyword: ");
    if (!fgets(key, sizeof key, stdin)) return 1;
    key[strcspn(key, "\r\n")] = '\0';
    build_square(key, square);
    puts("Playfair square (I/J share one cell):");
    for (int i = 0; i < 25; ++i) printf("%c%c", square[i], (i % 5 == 4) ? '\n' : ' ');

    printf("Encrypt (E) or Decrypt (D)? ");
    if (scanf(" %c", &mode) != 1) return 1;
    mode = (char)toupper((unsigned char)mode);
    if (mode != 'E' && mode != 'D') { puts("Enter E or D."); return 1; }
    getchar();
    printf("Enter message: ");
    if (!fgets(text, sizeof text, stdin)) return 1;

    if (mode == 'E') prepare_plaintext(text, prepared, sizeof prepared);
    else {
        size_t n = 0;
        for (size_t i = 0; text[i] && n + 1 < sizeof prepared; ++i) {
            unsigned char c = (unsigned char)toupper((unsigned char)text[i]);
            if (c >= 'A' && c <= 'Z') prepared[n++] = (char)(c == 'J' ? 'I' : c);
        }
        prepared[n] = '\0';
        if (n % 2 != 0) { puts("Ciphertext must contain an even number of letters."); return 1; }
    }
    size_t n = strlen(prepared);
    for (size_t i = 0; i + 1 < n; i += 2) transform_pair(square, &prepared[i], &prepared[i + 1], mode == 'D');
    printf("Result (letters only): ");
    for (size_t i = 0; i < n; ++i) printf("%c", prepared[i]);
    putchar('\n');
    if (mode == 'D') puts("Note: remove filler X/Q characters where appropriate; Playfair cannot always distinguish fillers from original letters.");
    return 0;
}
