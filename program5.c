
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mod26(int x)
{
    return ((x % 26) + 26) % 26;
}

int modInverse(int a)
{
    int i;

    for (i = 1; i < 26; i++)
        if ((a * i) % 26 == 1)
            return i;

    return -1;
}

void affineCipher(char text[], int a, int b, int decrypt)
{
    int i, p, c, inverse = -1;

    if (decrypt)
        inverse = modInverse(a);

    for (i = 0; text[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)text[i]))
        {
            int base = isupper((unsigned char)text[i]) ? 'A' : 'a';
            p = text[i] - base;

            if (!decrypt)
                c = mod26(a * p + b);
            else
                c = mod26(inverse * (p - b));

            text[i] = (char)(base + c);
        }
    }
}

int main(void)
{
    char text[1000];
    int a, b, choice;

    printf("Enter the text: ");
    if (fgets(text, sizeof(text), stdin) == NULL)
        return 1;
    text[strcspn(text, "\n")] = '\0';

    printf("Enter value of a: ");
    if (scanf("%d", &a) != 1)
    {
        printf("Invalid input.\n");
        return 1;
    }

    a = mod26(a);

    if (gcd(a, 26) != 1)
    {
        printf("Invalid a: gcd(a, 26) must equal 1.\n");
        printf("Allowed values: 1, 3, 5, 7, 9, 11, ");
        printf("15, 17, 19, 21, 23, 25.\n");
        return 1;
    }

    printf("Enter value of b: ");
    if (scanf("%d", &b) != 1)
    {
        printf("Invalid input.\n");
        return 1;
    }
    b = mod26(b);

    printf("1. Encrypt\n2. Decrypt\nEnter choice: ");
    if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2))
    {
        printf("Invalid choice.\n");
        return 1;
    }

    affineCipher(text, a, b, choice == 2);

    printf("Result: %s\n", text);
    return 0;
}
