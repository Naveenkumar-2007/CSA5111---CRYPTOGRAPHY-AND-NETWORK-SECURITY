#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char text[2048];
    char mode;
    int shift;

    printf("Caesar cipher: Encrypt (E) or Decrypt (D)? ");
    if (scanf(" %c", &mode) != 1) return 1;
    mode = (char)toupper((unsigned char)mode);
    if (mode != 'E' && mode != 'D') {
        puts("Invalid mode. Enter E or D.");
        return 1;
    }

    printf("Enter shift k (1-25): ");
    if (scanf("%d", &shift) != 1 || shift < 1 || shift > 25) {
        puts("Invalid shift. k must be between 1 and 25.");
        return 1;
    }
    getchar(); /* consume newline after the number */
    printf("Enter message: ");
    if (!fgets(text, sizeof text, stdin)) return 1;

    if (mode == 'D') shift = 26 - shift;
    for (size_t i = 0; text[i] != '\0'; ++i) {
        unsigned char ch = (unsigned char)text[i];
        if (ch >= 'A' && ch <= 'Z') text[i] = (char)('A' + (ch - 'A' + shift) % 26);
        else if (ch >= 'a' && ch <= 'z') text[i] = (char)('a' + (ch - 'a' + shift) % 26);
    }
    printf("Result: %s", text);
    return 0;
}
