#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void){
    float dollars;
    
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars <= 0);
    
    int cents = round(dollars * 100);
    int count = 0;
    
    while (cents > 0)
    {
        if (cents >= 25)
        {
            cents -= 25;
            count++;
        }else if (cents >= 10)
        {
            cents -= 10;
            count++;
        }else if (cents >= 5)
        {
            cents -= 5;
            count++;
        }else if (cents >= 1){
            cents -= 1;
            count++;
        }
    }
    
    printf("%i\n", count);
    
}