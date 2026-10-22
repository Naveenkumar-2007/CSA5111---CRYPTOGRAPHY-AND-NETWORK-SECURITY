#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char text[1000], key[200];
    int choice, i, j = 0, shift;

    printf("Enter the text: ");
    if (fgets(text, sizeof(text), stdin) == NULL)
        return 1;
    text[strcspn(text, "\n")] = '\0';

    printf("Enter alphabetic key: ");
    if (scanf("%199s", key) != 1)
        return 1;

    for (i = 0; key[i] != '\0'; i++)
    {
        if (!isalpha((unsigned char)key[i]))
        {
            printf("Invalid key. Use letters only.\n");
            return 1;
        }
        key[i] = (char)toupper((unsigned char)key[i]);
    }

    printf("1. Encrypt\n2. Decrypt\nEnter choice: ");
    if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2))
    {
        printf("Invalid choice.\n");
        return 1;
    }

    for (i = 0; text[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)text[i]))
        {
            int base = isupper((unsigned char)text[i]) ? 'A' : 'a';

            shift = key[j % strlen(key)] - 'A';

            if (choice == 1)
                text[i] = (char)(base + (text[i] - base + shift) % 26);
            else
                text[i] = (char)(base + (text[i] - base - shift + 26) % 26);

            j++;
        }
    }

    printf("Result: %s\n", text);
    return 0;
}
