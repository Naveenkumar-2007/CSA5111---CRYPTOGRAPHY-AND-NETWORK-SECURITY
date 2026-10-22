
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

void generateMatrix(const char key[])
{
    int used[26] = {0};
    int r = 0, c = 0, i;
    char ch;

    used['J' - 'A'] = 1;

    for (i = 0; key[i] != '\0'; i++)
    {
        if (!isalpha((unsigned char)key[i]))
            continue;

        ch = (char)toupper((unsigned char)key[i]);
        if (ch == 'J')
            ch = 'I';

        if (!used[ch - 'A'])
        {
            matrix[r][c++] = ch;
            used[ch - 'A'] = 1;

            if (c == 5)
            {
                c = 0;
                r++;
            }
        }
    }

    for (ch = 'A'; ch <= 'Z'; ch++)
    {
        if (!used[ch - 'A'])
        {
            matrix[r][c++] = ch;

            if (c == 5)
            {
                c = 0;
                r++;
            }
        }
    }
}

void findPosition(char ch, int *r, int *c)
{
    int i, j;

    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            if (matrix[i][j] == ch)
            {
                *r = i;
                *c = j;
                return;
            }
}

void playfair(char text[], int decrypt)
{
    char prepared[2000], result[2000];
    int n = 0, i, r1, c1, r2, c2;
    int shift = decrypt ? 4 : 1;

    /* Remove spaces/punctuation and replace J with I */
    for (i = 0; text[i] != '\0' && n < 1900; i++)
    {
        if (isalpha((unsigned char)text[i]))
        {
            char ch = (char)toupper((unsigned char)text[i]);
            if (ch == 'J')
                ch = 'I';
            prepared[n++] = ch;
        }
    }

    prepared[n] = '\0';

    /* Split into pairs, inserting X between repeated letters */
    i = 0;
    n = 0;

    while (prepared[i] != '\0' && n < 1995)
    {
        char a = prepared[i++];
        char b;

        if (prepared[i] == '\0')
            b = (a == 'X') ? 'Q' : 'X';
        else if (prepared[i] == a)
            b = (a == 'X') ? 'Q' : 'X';
        else
            b = prepared[i++];

        result[n++] = a;
        result[n++] = b;
    }

    result[n] = '\0';

    for (i = 0; i < n; i += 2)
    {
        findPosition(result[i], &r1, &c1);
        findPosition(result[i + 1], &r2, &c2);

        if (r1 == r2)
        {
            result[i] = matrix[r1][(c1 + shift) % 5];
            result[i + 1] = matrix[r2][(c2 + shift) % 5];
        }
        else if (c1 == c2)
        {
            result[i] = matrix[(r1 + shift) % 5][c1];
            result[i + 1] = matrix[(r2 + shift) % 5][c2];
        }
        else
        {
            result[i] = matrix[r1][c2];
            result[i + 1] = matrix[r2][c1];
        }
    }

    result[n] = '\0';
    printf("Result: %s\n", result);
}

int main(void)
{
    char key[100], text[1000];
    int choice, i, j;

    printf("Enter keyword: ");
    if (scanf("%99s", key) != 1)
        return 1;

    generateMatrix(key);

    printf("\nPlayfair Matrix:\n");
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
            printf("%c ", matrix[i][j]);
        printf("\n");
    }

    getchar();

    printf("\nEnter plaintext/ciphertext: ");
    if (fgets(text, sizeof(text), stdin) == NULL)
        return 1;
    text[strcspn(text, "\n")] = '\0';

    printf("1. Encrypt\n2. Decrypt\nEnter choice: ");
    if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2))
    {
        printf("Invalid choice.\n");
        return 1;
    }

    playfair(text, choice == 2);
    return 0;
}
