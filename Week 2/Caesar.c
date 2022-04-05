#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    int key, intchar;
    if(argc==2 && atoi(argv[argc-1])!= 0)
    {
        key= atoi(argv[argc-1]);
        string text= get_string("plaintext: ");
        printf("ciphertext: ");
        for(int i=0;text[i] != '\0';i++)
            {
                if(text[i]<= 'Z' && text[i]>= 'A')
                    {
                       text[i]= text[i] + key % 26;
                       if(text[i] > 'Z')
                       {
                           text[i] = 'A' + (text[i]-key) % 26;
                       }
                    }
                if(text[i]<= 'z' && text[i]>= 'a')
                    { 
                       intchar = text[i] + key % 26;
                       if(intchar > 'z' )
                       {
                           text[i] = intchar - 'z' + 'a' - 1;
                       }
                       else
                       {
                           text[i] = text[i] + key % 26;
                       }   
                    }
                printf("%c", text[i]);
            }
        printf("\n");
    }
    else if(argc==1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        printf("Usage: ./caesar key\n");
    }
    return 0;
}
