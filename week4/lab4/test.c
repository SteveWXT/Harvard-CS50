#include <stdint.h>
#include <stdio.h>

int main(void)
{
    int16_t buffer = 10;
    float factor = 0.5;
    printf("%i\n", buffer);
    printf("%f\n", factor * buffer);
    
}