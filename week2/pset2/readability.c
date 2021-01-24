#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text;
    int letters = 0;
    int words = 0;
    int sentences = 0;
    
    text = get_string("Text: ");
    
    letters = count_letters(text);
    words = count_words(text);
    sentences = count_sentences(text);
    
    float L = letters * 1.0 / words * 100;
    float S = sentences * 1.0 / words * 100;
    
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
    
}

int count_letters(string text)
{
    int count = 0;
    
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (islower(text[i]) || isupper(text[i]))
        {
            count++;
        }
    }
    
    return count;
}

int count_words(string text)
{
    int count = 0;
    
    for (int i = 0, n = strlen(text); i<n; i++)
    {
        if (isspace(text[i]))
        {
            count++;
        }
    }
    
    count++;
    
    return count;
}

int count_sentences(string text)
{
    int count = 0;
    
    for (int i = 0, n = strlen(text); i<n; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            count++;
        }
    }
     return count;
}