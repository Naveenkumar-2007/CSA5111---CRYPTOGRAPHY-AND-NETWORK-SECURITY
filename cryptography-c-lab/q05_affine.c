#include <stdio.h>
#include <string.h>
#include <ctype.h>

static int gcd(int a, int b) { while (b) { int t = b; b = a % b; a = t; } return a; }
static int inverse_mod26(int a) { for (int i = 1; i < 26; ++i) if ((a * i) % 26 == 1) return i; return -1; }

int main(void) {
    char mode, text[2048]; int a, b;
    printf("Affine cipher: Encrypt (E) or Decrypt (D)? ");
    if (scanf(" %c", &mode) != 1) return 1;
    mode = (char)toupper((unsigned char)mode);
    if (mode != 'E' && mode != 'D') { puts("Enter E or D."); return 1; }
    printf("Enter a (must be relatively prime to 26): ");
    if (scanf("%d", &a) != 1) return 1;
    printf("Enter b (any integer; normalized modulo 26): ");
    if (scanf("%d", &b) != 1) return 1;
    a = ((a % 26) + 26) % 26; b = ((b % 26) + 26) % 26;
    if (gcd(a, 26) != 1) { puts("Invalid a: gcd(a, 26) must equal 1."); return 1; }
    int inv = inverse_mod26(a);
    getchar();
    printf("Enter message: ");
    if (!fgets(text, sizeof text, stdin)) return 1;
    for (size_t i = 0; text[i]; ++i) {
        unsigned char c = (unsigned char)text[i];
        if (c >= 'A' && c <= 'Z') {
            int x = c - 'A'; int y = mode == 'E' ? (a * x + b) % 26 : (inv * (x - b + 26)) % 26;
            text[i] = (char)('A' + y);
        } else if (c >= 'a' && c <= 'z') {
            int x = c - 'a'; int y = mode == 'E' ? (a * x + b) % 26 : (inv * (x - b + 26)) % 26;
            text[i] = (char)('a' + y);
        }
    }
    printf("Result: %s", text);
    puts("\nTheory: b may be any value modulo 26. Valid a values: 1,3,5,7,9,11,15,17,19,21,23,25.");
    return 0;
}
