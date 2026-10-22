
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int validKey(const char key[])
{
    int seen[26] = {0};
    int i;

    if (strlen(key) != 26)
        return 0;

    for (i = 0; i < 26; i++)
    {
        if (!isalpha((unsigned char)key[i]))
            return 0;

        int x = toupper((unsigned char)key[i]) - 'A';
        if (seen[x])
            return 0;

        seen[x] = 1;
    }
    return 1;
}

void substitute(char text[], const char key[], int decrypt)
{
    int i;

    for (i = 0; text[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)text[i]))
        {
            int x = toupper((unsigned char)text[i]) - 'A';
            int j;

            if (!decrypt)
                j = toupper((unsigned char)key[x]) - 'A';
            else
            {
                for (j = 0; j < 26; j++)
                    if (toupper((unsigned char)key[j]) - 'A' == x)
                        break;
            }

            text[i] = isupper((unsigned char)text[i])
                     ? (char)('A' + j)
                     : (char)('a' + j);
        }
    }
}

int main(void)
{
    char key[100], text[1000];
    int choice;

    printf("Enter 26-letter substitution key: ");
    if (scanf("%99s", key) != 1 || !validKey(key))
    {
        printf("Invalid key. Use each letter A-Z exactly once.\n");
        return 1;
    }

    getchar(); /* Consume newline */

    printf("Enter the text: ");
    if (fgets(text, sizeof(text), stdin) == NULL)
        return 1;
    text[strcspn(text, "\n")] = '\0';

    printf("1. Encrypt\n2. Decrypt\nEnter choice: ");
    if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2))
    {
        printf("Invalid choice.\n");
        return 1;
    }

    substitute(text, key, choice == 2);

    printf("Result: %s\n", text);
    return 0;
}
