#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAXSTD 100
#define MAXITEMS 10
#define STLEN 51
/* Name: Tsehai Boucaud
Date: 11/30/2020
Purpose: To demonstrate understanding of files by importing student data (name, grades, ID, etc) from a text file and exporting a summary to another text file. A search function is also used to lookup a specific student.*/
char getLetterGrade(float score);
int getMaxTotalIdx(float totals[], int n);
void writeData(FILE *out, char ids[][STLEN], char names[][STLEN],  float totals[], int n);

int lookup(char s[][STLEN], char key[STLEN], int n)//searches for a specific name given a string array and a string key, as well as the size of the string array.
{
  for(int i = 0; i < n; i++)
  {
    if(strcmp(s[i], key) == 0)
    {
      return i;
    }
  }
  return -1;
}

void to_lower(char *str)//converts all characters in a string parameter to lower case.
{
  for(int i = 0; str[i] != '\0'; i++)
  {
    {
      str[i] = tolower(str[i]);
    }
  }
}

int lookup(char names[][STLEN], char key[STLEN], int n); 

int main()
{
  char ids[MAXSTD][STLEN]; //for string ids
  char names[MAXSTD][STLEN];// for storing last names
  float grades[MAXSTD][MAXITEMS]; // for storing grades
  float totals[MAXSTD]; //for storing totals

  FILE *out, *inp; //points to files grades.txt and summary.txt, respectively.
  inp = fopen("grades.txt", "r");
  out = fopen("summary.txt", "w");
  
  if(inp == NULL || out == NULL)
  {
    printf("Cannot open file\n");
    exit(1);
  }

  int n, g; //counter variables.
  fscanf(inp, "%d %d", &n, &g); //gets n and g from the file grades.txt

  for(int i = 0; i < n; i++) //stores all of the grades.txt file data into the corresponding arrays.
  {
    fscanf(inp, "%s", ids[i]);
    fscanf(inp, "%s", names[i]);

    fscanf(inp, "%f %f", &grades[i][0], &grades[i][1]);

    for(int j = 2; j < g + 2; j++)
    {
      fscanf(inp, "%f", &grades[i][j]);
    }
  }
float quiztotal = 0.0; //float double to contain totals.
  for(int i = 0; i < n; i++) 
  {
    quiztotal = 0.0;
    for(int j = 2; j < g + 2; j++)
    {
      quiztotal += grades[i][j];
    }
    totals[i] = 0.35 * grades[i][0] + 0.4 * grades[i][1] + 0.25 * (quiztotal * 1.0 / g);
  }

  writeData(out, ids, names, totals, n);//calls the writeData function with arrays of data to write the summary file.
  printf("Data written in summary.txt file\n");
  
  char lastName[STLEN]; //variable to contain user search.
  printf("Enter a last name to search: ");
  scanf("%s", lastName);
  to_lower(lastName);

  int searchIdx = lookup(names, lastName, n);
  if(searchIdx != -1) //as long as the lookup function does not return -1 (meaning invalid input), the details of the name found will be printed.
  {
    printf("%s was found in the list. Here is the details: \n", lastName);
    printf("ID: %s Lname: %s Total: %.2f\n", ids[searchIdx], names[searchIdx], totals[searchIdx]);
    printf("Grades: \n");
    printf("Midterm: %.2f, Final term: %.2f, quizzes: \n", grades[searchIdx][0], grades[searchIdx][1]);

    for(int j = 2; j < g + 2; j++)
    {
      printf("%.2f ", grades[searchIdx][j]);
    }
  }
  else
  {
    printf("%s not found in the list.\n", lastName);
  }
  //close all files opened.
  fclose(inp);
  fclose(out);
}

char getLetterGrade(float score) //converts float score into a corresponding letter grade.
{
  if(score >= 90)
    return 'A';
  else if(score >= 80)
    return 'B';
  else if(score >= 70)
    return 'C';
  else
    return 'F';
}
int getMaxTotalIdx(float totals[], int n) //finds the highest total score in the totals array and returns its index.
{
  int maxindex = 0;
  for(int i = 1; i < n; i++)
  {
    if(totals[maxindex] < totals[i])
    {
      maxindex = i;
    }
  }
  return maxindex;
}

void writeData(FILE *out, char ids[][STLEN], char names[][STLEN],  float totals[], int n) //writes the data to summary.txt.
{
  fprintf(out, "Summary of students: "); //print to file
  fprintf(out, "\n========\n");

  printf("Summary of students: "); //output to console
  printf("\n========\n");

  for(int i = 0; i < n; i++)//summarize the data of all students in file and to console
  {
    fprintf(out, "ID: %s Lname: %s Total: %.2f Grade: %c\n", ids[i], names[i], totals[i], getLetterGrade(totals[i]));
    printf("ID: %s Lname: %s Total: %.2f Grade: %c\n", ids[i], names[i], totals[i], getLetterGrade(totals[i]));
  }
  fprintf(out, "\n========\n");//print to file
  printf("\n========\n");//print to console

  int maxIdx = getMaxTotalIdx(totals, n);//find and output student with highest total to file and console.
  fprintf(out, "First student with the highest total is %s %s %.2f\n", ids[maxIdx], names[maxIdx], totals[maxIdx]);
  printf("First student with the highest total is %s %s %.2f\n", ids[maxIdx], names[maxIdx], totals[maxIdx]);
}