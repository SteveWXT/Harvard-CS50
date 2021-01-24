#include <stdio.h>
#include <cs50.h>

void pyramid(int);

int main(void){
    
    int height;
    
    do
    {
        height = get_int("Height: ");
    }
    while (height<1 || height>8);
    
    pyramid(height);
    
}

void pyramid(int n){
 
 for (int h=1; h<=n; h++){
       
        for (int i=0; i<n-h; i++){
            printf(" ");
        }
        
        for (int j=0; j<h; j++){
            printf("#");
        }
        
        printf("  ");
        
        for (int k=0; k<h; k++){
            printf("#");
        }
        
        
        printf("\n");
    }
}