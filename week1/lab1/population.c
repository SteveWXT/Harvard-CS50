#include <cs50.h>
#include <stdio.h>

int main(void)
{
  int start = 0;
  int end = 0;
  int year = 0;
  
  
  do
  {
      start = get_int("Start size: ");
  }
  while(start < 9);
  
  do
  {
     end = get_int("End size: ");
  }
  while(end < start);
  
  
  do
  {
      int born = start/3;
      int dead = start/4;
      
      start = start + born - dead;
      year++;
      
  }
  while(start < end);
  
  printf("Years: %i\n", year);
  
    
}