#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    const int AE = 1;
    const int MC = 2;
    const int Visa = 3;
    
    int brand = 0;
    long card = 0;
    int count = 0;
    
    do
    {
         card = get_long("Number: ");
    }
    while (card <= 0);
    
    for (long temp = card; temp > 0; count++)
    {
        temp /= 10;
    }
            

    
    
    //Luhn's algorithm
    long temp = card;
    int sumLast = 0;
    int sumSec2Last = 0;
    int sum = 0;
    
    int tempX = 0;
    
    while (temp > 0)
    {
        sumLast += temp % 10;
        temp /= 10;
        
        if (temp > 0)
        {
            tempX = temp % 10 * 2;
            if ( tempX < 10)
            {
                sumSec2Last += tempX;
            }
            else
            {
                sumSec2Last += tempX % 10 + tempX / 10;
            }
            
            temp /= 10;
        }
    }
    
    sum = sumLast + sumSec2Last;

    
    if (sum%10 != 0)
    {
        printf("INVALID\n");
    }
    else if (count!=13 && count!=15 && count!=16)
    {
        printf("INVALID\n");
    }
    else
    {

        if (count == 13)
        {
            if (card/(long)pow(10, 12) == 4)
            {
                brand = Visa;
            }
        }
        else if (count == 15)
        {
            if (card / (long)pow(10, 13) == 34 || card / (long)pow(10, 13) == 37)
            {
                brand = AE;
            }
        }
        else
        {
            if (card / (long)pow(10, 14) >= 51 && card / (long)pow(10, 14) <=55)
            {
                brand = MC;
            }
            
            if (card / (long)pow(10, 15) == 4 )
            {
                brand = Visa;
            }
            
        }
        
        if (brand == AE)
        {
        printf("AMEX\n");
        }
        else if (brand == MC)
        {
            printf("MASTERCARD\n");    
        }
        else if (brand == Visa)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    
    
    
    
    
}