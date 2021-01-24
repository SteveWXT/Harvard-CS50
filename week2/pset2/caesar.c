#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    //check one CL argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    //check argument is a number
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    
    //convert key from string to int
    int key = atoi(argv[1]);
    
    //prompt user for plaintext 
    string plain = get_string("plaintext: ");
    
    //iterate every character
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        if (isupper(plain[i]))
        {
            printf("%c", (plain[i] - 65 + key) % 26 + 65);
        }
        else if (islower(plain[i]))
        {
            printf("%c", (plain[i] - 97 + key) % 26 + 97);
        }
        else
        {
            printf("%c", plain[i]);
        }
    }
    
    //print a new line
    printf("\n");
    
    return 0;
}