#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int shift(char letter);

int main(int argc, string argv[])
{
    int key, intchar, flag = 1, notLetter = 0;
    if (argc == 2 && argv[argc - 1] != NULL)
    {
        for (int i = 0, n = strlen(argv[argc - 1]); i < n; i++)
        {
            if (isalpha(argv[argc - 1] [i]) == 0)
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
        { 
            string text = get_string("plaintext: ");
            printf("ciphertext: ");
            for (int i = 0, n = strlen(argv[argc - 1]); text[i] != '\0'; i++)
            {
                if (isalpha(text[i]) == 0)
                {
                    notLetter++;
                }
                key = shift(argv[argc - 1] [(i - notLetter) % n]);
                if (isupper(text[i]) != 0)
                {
                    text[i] = text[i] + key;
                    if (text[i] > 'Z')
                    {
                        text[i] = text[i] - 'Z' + 'A' - 1;
                    }
                }
                else if (islower(text[i]) != 0)
                {
                    intchar = text[i] + key;
                    if (intchar <= 'z')
                    {
                        text[i] = intchar;
                    }
                    else
                    {
                        text[i] = intchar - 'z' + 'a' - 1;
                    }
                }
                printf("%c", text[i]);
            }
            printf("\n"); 
            return 0;
        }
        else
        {
            printf("Usage: ./vigenere keyword\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
}
int shift(char letter)
{
    if (isupper(letter) != 0)
    {
        return (letter - 'A');
    }
    else if (islower(letter) != 0)
    {
        return (letter - 'a');
    }
    else
    {
        return 0;
    }
}
