#include <stdio.h>
#define MAXCOLUMNS 100
#define MAXROWS 100
/*
Name: Tsehai Boucaud
Date: 11/10/2020
Purpose: To perform different operations and manipulations on user inputted matrices.
*/
void displayMatrix(int array[][MAXCOLUMNS], int numRow, int numCol) //Displays a matrix given a 2d array and its amount of rows and columns
{
  for(int i = 0; i < numRow; i++)
  { 
    for(int j = 0; j < numCol; j++)
    {
      printf("%4d", array[i][j]);
    }
    printf("\n");
  }
}
void findMaxPerRow(int array[][MAXCOLUMNS], int numRow, int numCol) //finds and displays the maximum value in every row of a matrix given given a 2d array and its amount of rows and columns
{
  int max = 0;
  for(int i = 0; i < numRow; i++)
  { 
    for(int j = 0; j < numCol; j++)
    {
      if(array[i][j] > max)
        max = array[i][j];
    }
    printf("max of row %d is %d\n",i, max);
    max = 0;
  }
}
void printLLTriangle(int array[][MAXCOLUMNS], int numRow, int numCol) //prints a pattern that displays the values of only the lower left triangle of a matrix, and replaces all other values with 0, given a 2d array and its amount of rows and columns
{
  for(int i = 0; i < numRow; i++)
  { 
    for(int j = 0; j < numCol; j++)
    {
      if(j <= i)
        printf("%4d", array[i][j]);
      else
        printf("%4d", 0);
    }
    printf("\n");
  }
}
void printURTriangle(int array[][MAXCOLUMNS], int numRow, int numCol) //Does the same thing as the Lower Left Triangle function (printLLTriangle) except the upper right instead, given a 2d array and its amount of rows and columns.
{
  for(int i = 0; i < numRow; i++)
  { 
    for(int j = 0; j < numCol; j++)
    {
      if(j >= i)
        printf("%4d", array[i][j]);
      else
        printf("%4d", 0);
    }
    printf("\n");
  }
}
void addMatrix(int arr1[][MAXCOLUMNS], int arr2[][MAXCOLUMNS], int sum[][MAXCOLUMNS], int numRow, int numCol) //adds two matrices together and puts the resulting matrix in a 2d array, given a blank 2d array, 2 2d arrays with values, and the sizes of these arrays. Precondition: 2d Arrays must all be the same size.
{
  for(int i = 0; i < numRow; i++)
  { 
    for(int j = 0; j < numCol; j++)
    {
      sum[i][j] = arr1[i][j] + arr2[i][j];
    }
  }
}
int sumSurrounding(int arr1[][MAXCOLUMNS], int numRow, int numCol, int i, int j)//Finds the sum of all integers surrounding a specific location within a matrix, given the row/column coordinates (i and j) of this location, as well as a 2d array representing the matrix and the amount of rows and columns in this 2d array.
{
  int sum = 0;
  for(int r = 0; r < numRow; r++)
  { 
    for(int c = 0; c < numCol; c++)
    {
        if(r == i+1 && c <= j+1 && c >= j-1)
          sum+= arr1[r][c];
        else if(r == i-1 && c <= j+1 && c >= j-1)
          sum+= arr1[r][c];
        else if(r == i && c <= j+1 && c >= j-1 && c!= j)
          sum+= arr1[r][c];
        else;
    }
  }
  return sum;
}
int main(void) {
  int arr1[MAXROWS][MAXCOLUMNS], arr2[MAXROWS][MAXCOLUMNS], arr3[MAXROWS][MAXCOLUMNS];//defining all 2d arrays
  int r, c;//defining the variables that will contain the row and column sizes of the 2d arrays
  printf("enter number of rows and columns:");//prompting and displaying amount of rows and columns to be used in both arrays
  scanf("%d %d", &r, &c);
  printf("input for matrix 1:\n"); //prompting and displaying 1st user inputted 2d array
   for(int i = 0; i < r; i++)
  { 
    printf("data for matrix1[%d][0] to matrix1[%d][%d]", i, i, (c-1));
    for(int j = 0; j < c; j++)
    {
      scanf("%d", &arr1[i][j]);
    }
  }
  printf("input for matrix 2:\n"); //prompting and displaying 2nd user inputted 2d array
   for(int i = 0; i < r; i++)
  { 
    printf("data for matrix2[%d][0] to matrix2[%d][%d]", i, i, (c-1));
    for(int j = 0; j < c; j++)
    {
      scanf("%d", &arr2[i][j]);
    }
  }

  //printing all outputs
  printf("\nprinting matrix 1:\n");
  displayMatrix(arr1, r, c);
  printf("printing matrix 2:\n");  
  displayMatrix(arr2, r, c);
  printf("\nprinting max per row for matrix 1:\n"); 
  findMaxPerRow(arr1, r, c);
  printf("\nprinting lower left triangle of matrix 1:\n");
  printLLTriangle(arr1, r, c);;
  printf("\nprinting upper right triangle for matrix 1:\n");
  printURTriangle(arr1, r, c);
  printf("\nmatrix 1 + matrix 2 is:\n");
  addMatrix(arr1, arr2, arr3, r, c);
  displayMatrix(arr3, r, c);

  int i = 0, j = 0, sum = 0; //defining variables needed for sumSurrounding function
  while(i >= 0 && j >= 0) //user exits loop by inputting a negative number
  {
    printf("enter i and j for calculating sum of surrounding:");
    scanf("%d %d\n", &i, &j);
    if(i < 0 || j < 0)
      break;
    sum = sumSurrounding(arr1, r, c, i, j);
    printf("sum of surrounding is %d\n", sum);
    sum = 0;
  }
  printf("Exit");
  return 0;
}
