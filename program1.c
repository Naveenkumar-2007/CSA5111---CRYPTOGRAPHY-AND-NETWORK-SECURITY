
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void caesarCipher(char text[], int key)
{
    int i;
    key = ((key % 26) + 26) % 26;

    for (i = 0; text[i] != '\0'; i++)
    {
        if (isupper((unsigned char)text[i]))
            text[i] = (char)('A' + (text[i] - 'A' + key) % 26);
        else if (islower((unsigned char)text[i]))
            text[i] = (char)('a' + (text[i] - 'a' + key) % 26);
    }
}

int main(void)
{
    char text[1000];
    int key, choice;

    printf("Enter the text: ");
    if (fgets(text, sizeof(text), stdin) == NULL)
        return 1;
    text[strcspn(text, "\n")] = '\0';

    printf("Enter key (1-25): ");
    if (scanf("%d", &key) != 1 || key < 1 || key > 25)
    {
        printf("Invalid key. Enter a number from 1 to 25.\n");
        return 1;
    }

    printf("1. Encrypt\n2. Decrypt\nEnter choice: ");
    if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2))
    {
        printf("Invalid choice.\n");
        return 1;
    }

    if (choice == 2)
        key = 26 - key;

    caesarCipher(text, key);

    printf("Result: %s\n", text);
    return 0;
}
