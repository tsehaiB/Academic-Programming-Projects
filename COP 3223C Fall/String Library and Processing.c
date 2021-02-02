#include <stdio.h>
#include <ctype.h>
#define MAX_LENGTH 101
/*
Name: Tsehai Boucaud
Date: 11/25/2020
Purpose: to demonstrate understanding of strings by manipulating user inputted strings to output the length, compare them, check to see if it is a palindrome string, and capitalize it.
*/
int getLength(char s[]) //finds the length of a string by incrimenting a counter every time a new character that is not the terminating '\0' character is found
{
  int counter = 0;
  for(int i = 0; s[i] != '\0'; i++)
  {
    counter++;
  }
  return counter;
}

int is_equal(char s1[], char s2[]) //compares two strings to see if they are the same, returns an integer of 1 or 0 to be treated as a boolean
{
  int equal = 0;
  for(int i = 0; s1[i] == s2[i] && equal == 0; i++)
  {
    if(s1[i] == '\0' || s2[i] == '\0')
    {
      equal = 1;
    }
  }
  return equal;
}

void str_copy(char dest[], char source[]) //copies one string into another.
{
  int i = 0;
  for(i = 0; source[i] != '\0'; i++)
  {
    dest[i] = source[i];
  }
  dest[i] = '\0';
}

void swap(char *a, char *b) //swaps two characters
{
  char temp = *a;
  *a = *b;
  *b = temp;
}

void str_reverse(char s[]) //reverses an entire string by swapping half of the characters at the start with the ones at the end.
{
  int len = getLength(s);
  for(int i = 0; i < len/2; i++)
  {
    swap(&s[i], &s[len-i-1]);
  }
}

int is_palindrome(char s[]) //checks to see if a string is a palindrome by using str_copy, str_reverse, and is_equal in sucession to return the boolean given in is_equal(copy, s).
{
  char copy[MAX_LENGTH];
  str_copy(copy, s);
  str_reverse(copy);
  if(is_equal(copy, s))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
void capitalize_word(char *str)//capitalizes the first letter in a string.
{
  for(int i = 0; str[i] != '\0'; i++)
  {
    if(i == 0 && str[i] != ' ')
    {
      str[i] = toupper(str[i]);
      continue;
    }
    if(str[i] == ' ')
    {
      i = i + 1;
      str[i] = toupper(str[i]);
      continue;
    }
    else
    {
      str[i] = tolower(str[i]);
    }
  }
}

int main(void) {
  //defining variables
  char s1[MAX_LENGTH], s2[MAX_LENGTH];
  char x;


  //prompting and assigning user input of two strings
  printf("Enter a string: ");
  scanf("%[^\n]s", s1);

  while((x=getchar() != '\n') && x != EOF); //loop to discard \n from last input and not to skip the next input

  printf("Enter another string: ");
  scanf("%[^\n]s", s2);

  //outputting the result of getLength with s1 and s2
  printf("\nThe length of your first string is %d\n", getLength(s1));
  printf("The length of your second string is %d\n", getLength(s2));

  //outputting the result of is_equal(s1, s2)
  if(is_equal(s1, s2)==1)
  {
    printf("You entered two equal strings.\n");
  }
  else
  {
    printf("Your strings are different.\n");
  }

  //outputting the result of is_palindrom(s1)
  if(is_palindrome(s1)) 
  {
      printf("%s is a palindrome string\n", s1);
  }
  else
  {
      printf("%s is not a palindrome string\n", s1);

  }

  //calling and outputting the capitalize_word function with parameter s1.
  capitalize_word(s1);
  printf("Capitalized s1 is %s ", s1);


  return 0;
}