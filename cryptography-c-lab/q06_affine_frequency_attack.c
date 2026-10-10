#include <stdio.h>
#include <string.h>

/* Assumption: most frequent plaintext E maps to ciphertext B,
   and second-most frequent plaintext T maps to ciphertext U. */
int main(void) {
    char ciphertext[2048];
    const int b = 15, inverse_a = 9;
    printf("Assuming E->B and T->U, the affine key is a=3, b=15.\n");
    printf("Enter ciphertext to decrypt: ");
    if (!fgets(ciphertext, sizeof ciphertext, stdin)) return 1;
    for (size_t i = 0; ciphertext[i]; ++i) {
        unsigned char c = (unsigned char)ciphertext[i];
        if (c >= 'A' && c <= 'Z') {
            int x = c - 'A'; ciphertext[i] = (char)('A' + (inverse_a * (x - b + 26)) % 26);
        } else if (c >= 'a' && c <= 'z') {
            int x = c - 'a'; ciphertext[i] = (char)('a' + (inverse_a * (x - b + 26)) % 26);
        }
    }
    printf("Decrypted text: %s", ciphertext);
    puts("If the frequency assumptions are wrong for a particular text, try other likely plaintext-letter assignments.");
    return 0;
}
