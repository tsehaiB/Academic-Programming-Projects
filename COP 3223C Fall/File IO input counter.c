#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
/* Name: Tsehai Boucaud
Date: 11/30/2020
Purpose: Demonstrating understanding of files by counting all of the different character types (vowels, digits, totla characters) and outputting summarized information to the user and data to the output file.*/

int main(void)
{
  FILE *inp, *out; //file variables for input.txt and output.txt, respectively.
  int charCount = 0, vowelCount = 0, digitCount = 0; //counters for vowel, character, and digit.
  inp = fopen("input.txt", "r");
  out = fopen("output.txt", "w");

  char str[100];//string variable to contian file data
  while(fgets(str, 500, inp) != NULL) //loop until the end of the file.
  {
    printf("%s", str);
    for(int i = 0; i < strlen(str); i++)//loop until the end of a line
    {
      if(str[i] != '\n')//if it's not the end of a line
      {
        charCount++;
      }
      if(tolower(str[i]) == 'a' || tolower(str[i]) == 'e' || tolower(str[i]) == 'i' || tolower(str[i]) == 'o' || tolower(str[i]) == 'u')//if it's a vowel, uppercase or lowercase.
      {
        vowelCount++;
      }
      if(str[i] > 47 && str[i] < 58) //if it's a digit
      {
        digitCount++;
      }
    }  
    for (int i = 0; str[i]!='\0'; i++) //for all characters in string str.
    {
      if(str[i] >= 'a' && str[i] <= 'z')
      {
        str[i] = str[i] -32;
      }
    }
    fscanf(out, "%s", str);
  }

  printf("\nNumber of characters: %d\n", charCount);
  printf("Number of vowels: %d\n", vowelCount);
  printf("Number of digits: %d\n", digitCount);
  return 0;
}