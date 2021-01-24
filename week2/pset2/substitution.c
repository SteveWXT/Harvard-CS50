#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    int key_upper[26];
    
    //check one CL argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
    //check whether argument is valid
    
    //length = 26
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    
    //alphabetic & each letter once
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Key can only be letters.\n");
            return 1;
        }
        
        for (int j = 0; j < i; j++)
        {
            if (argv[1][j] == argv[1][i])
            {
                printf("Key cannot contain the same letter.\n");
                return 1;
            }
        }
        
        key_upper[i] = toupper(argv[1][i]);
        
    }
   
    
   
    //prompt user for plaintext 
    string plain = get_string("plaintext: ");
    
    //iterate every character
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        if (isupper(plain[i]))
        {
            printf("%c", key_upper[plain[i] - 65]);
        }
        else if (islower(plain[i]))
        {
            printf("%c", key_upper[plain[i] - 97] + 32);
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