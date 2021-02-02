#include<stdio.h>
#define SIZE 200
/* Name: Tsehai Boucaud
Date: 11/3/2020
Purpose: To find all matching prime numbers in two user inputted lists, and output them, aswell as the amount found and the largest and smallest values in the second list.*/
int MinNum(int arrTwo[], int sizeTwo) //Function to find the smallest number in the second list
{
  int min = 100000;
  for(int i = 0; i < sizeTwo; i++)
    if(arrTwo[i] < min)
      min = arrTwo[i];
  return min;
}
int MaxNum(int arrTwo[], int sizeTwo) //Function to find largest number in the second list
{
  int max = 0;
  for(int i = 0; i < sizeTwo; i++)
    if(arrTwo[i] > max)
      max = arrTwo[i];
  return max;
}
int isPrime(int x) //Function that determines if a number sent to it is prime or not
{
 
  int prime = 1;
  if(x == 1)
  {
    prime = 0;
  }
  for(int i = 2; i < x; i++)  
  {
    if((x % i) == 0)
      prime = 0;
  }
    return prime;
}
void PrimeMatching(int arrOne[], int sizeOne, int arrTwo[], int sizeTwo) //Function that takes two user inputted lists, passes all of the numbers in the first list through the isPrime function, and then compares all prime numbers found to see if their is a matching prime in list two
{
  printf("Common prime numbers are: ");
  int prime = 0, commonCount = 0;
  for(int i = 0; i < sizeOne; i++)
  {
    prime = isPrime(arrOne[i]); //sets flag variable prime to 1 or 0 depending on if the number in the list is prime
    if(prime)//if a prime number is found in list 1
      for(int a = 0; a < sizeTwo; a++)
        if(arrTwo[a] == arrOne[i])//see if there is a pair in list two
        {
          printf("%d ", arrTwo[a]);
          commonCount++; //iterates whenever a new pair is found
          break;
        } 
        
  }
  printf("\n");
  printf("Common count: %d\n", commonCount);
}
int main(void)
{ 
  int arr1[SIZE], arr2[SIZE], size1, size2, min, max; //defining list variables, and variables to hold the smallest and largest values of list two
  //prompting and assigning user inputted list sizes and values.
  printf("Enter n and m: ");
  scanf("%d %d", &size1, &size2);
  printf("Enter data for first list: ");
  for(int x = 0; x < size1; x++)
  {
    //printf("x = %d", x);
    scanf("%d", &arr1[x]);
  }
  printf("Enter data for second list: ");
  for(int x = 0; x < size2; x++)
  {
    scanf("%d", &arr2[x]);
  }

  PrimeMatching(arr1, size1, arr2, size2); //finds and outputs all matching primes
  
  //finding and outputting minimum and maximum list two values
  min = MinNum(arr2, size2);
  printf("Smallest number in the second list: %d\n", min);
  max = MaxNum(arr2, size2);
  printf("Largest number in the second list: %d", max);
  return 0;
}