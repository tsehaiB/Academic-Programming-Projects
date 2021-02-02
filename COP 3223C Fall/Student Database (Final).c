#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXENROLL 5000 
#define MAXCOURSE 100
#define MAXSTUDENTS 2000

typedef struct Student{//no more than 2000
  int id;
  char firstName[100];//assumes name is no longer than 99 characters
  char lastName[100];//makes same assumption ^^
  int dayOB, monthOB, yearOB;
}Student;
typedef struct Course{//no more than 100
  char  courseID[100];
  char courseName[51];//50+1
  float totalCredit;
}Course;
typedef struct Enrollments{//no more than 5000
  int stuId;
  char couID[100];
  char semester[100];//assumes semester not longer than 99 characters.
  float score;
}Enrollments;

struct Student* loadStudent(int *i)//Function loads student by opening students.txt file and dyamically allocating memory to create a structure of students that holds all student data. Returns this structure and modified a size pointer to reflect the amount of students loaded.
{
  Student *stemp;
  stemp = (struct Student*)malloc(MAXSTUDENTS*sizeof(struct Student));
  FILE *input;
  input = fopen("students.txt", "r");

   while(fscanf(input, "%d %s %s %d %d %d", &stemp[*i].id, stemp[*i].firstName, stemp[*i].lastName, &stemp[*i].dayOB, &stemp[*i].monthOB, &stemp[*i].yearOB) != EOF)
  {
    *i = *i+1;
  }
  stemp = (struct Student*)realloc(stemp,(*i*sizeof(struct Student)));
  return stemp;
}
struct Course* loadCourse(int *i)//Function loads courses by opening courses.txt file and dyamically allocating memory to create a structure of courses that holds all course data. Returns this structure and modified a size pointer to reflect the amount of courses loaded.
{
  Course *ctemp;
  ctemp = (struct Course*)malloc(MAXCOURSE*sizeof(struct Course));
  FILE *input;
  input = fopen("courses.txt", "r"); 

   while(fscanf(input, "%s %s %f", ctemp[*i].courseID, ctemp[*i].courseName, &ctemp[*i].totalCredit) != EOF)
  {
    *i = *i+1;
  }
  ctemp = (struct Course*)realloc(ctemp,(*i*sizeof(struct Course)));
  return ctemp;
}
struct Enrollments* loadEnroll(int *i)//Function loads enrollments by opening enrollment.txt file and dyamically allocating memory to create a structure of enrollments that holds all enrollment data. Returns this structure and modified a size pointer to reflect the amount of enrollments loaded.
{
  Enrollments *etemp;
  etemp = (struct Enrollments*)malloc(MAXENROLL*sizeof(struct Enrollments));
  FILE *input;
  input = fopen("enrollment.txt", "r"); 
  /*
  int stuId;
  char courseID[100];
  char semester[100];//assumes semester not longer than 99 characters.
  float score;*/
   while(fscanf(input, "%d %s %s %f", &etemp[*i].stuId, etemp[*i].couID, etemp[*i].semester, &etemp[*i].score) != EOF)
  {
    *i = *i+1;
  }
  etemp = (struct Enrollments*)realloc(etemp,(*i*sizeof(struct Enrollments)));
  return etemp;
}
char calcGrade(float num)//Translates a float grade into its equivilant letter grade according to the grading system given to us in the assignment
{
   if(num > 90)
      return 'A';
    else if(num >= 80)
      return'B';
    else if(num >= 70)
      return 'C';
    else if(num >= 60)
      return 'D';
    else
      return 'F';
}
void search_student(Student ArrayOfStudents[], int amountStudents, Course ArrayOfCourses[], int amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls, char search[], int x)//Searches for student using for loops and switch cases by Last name, first name, ID, or yearOB. Uses atoi function for the last two to turn string data into comparabed int data
{
  int found = 0;
  for(int index = 0; index < amountStudents; index++)
{
  int i = 0, flag = 0;
  switch(x)
  {
    case 1:
    {
        if(!strcmp(search, ArrayOfStudents[index].lastName))
        {
          found = 1;
          flag = 1;
          i = index;
        }
      break;
    }
    case 2:
    {
        if(!strcmp(search, ArrayOfStudents[index].firstName))
        {
          found = 1;
          flag = 1;
          i = index;
        }
        break;
    }
    case 3:
    {
        if(ArrayOfStudents[index].id == atoi(search))
        {
          found = 1;
          flag = 1;
          i = index;
        }
        break;
    }
    case 4:
    {
        if(ArrayOfStudents[index].yearOB == atoi(search))
        {
          found = 1;
          flag = 1;
          i = index;
        }
        break;
    }
  }
  if(flag)//if the student is found, print all expected data about them.
  {
          printf("------------------\n");
          printf("%d %s %s %d/%d/%d\n", ArrayOfStudents[i].id, ArrayOfStudents[i].firstName, ArrayOfStudents[i].lastName, ArrayOfStudents[i].monthOB, ArrayOfStudents[i].dayOB, ArrayOfStudents[i].yearOB);
          for(int j = 0; j < amountEnrolls; j++)//nested loops to find linked information from other arrays
          {
            if(ArrayOfEnrollments[j].stuId == ArrayOfStudents[i].id)
            {
              
              for(int t = 0; t < amountCourses; t++)
              {
                if(!strcmp(ArrayOfEnrollments[j].couID, ArrayOfCourses[t].courseID))
                {
                  printf("%s %s ", ArrayOfCourses[t].courseID, ArrayOfCourses[t].courseName);
                }
              }
              
              printf("%s %.0f %c\n", ArrayOfEnrollments[j].semester, ArrayOfEnrollments[j].score, calcGrade(ArrayOfEnrollments[j].score));
            }              
          }  
  }
    
  }
  if(found == 0)
  {
    printf("------------------\n");
    printf("not found\n");
  }
  printf("------------------\n");
}
void search_courseID(Student ArrayOfStudents[], int amountStudents, Course ArrayOfCourses[], int amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls, char searchCourse[])//searches for a course by courseID and prints relevant information
{
  int found = 0;
  for(int i = 0; i < amountCourses; i++)
  {
    if(!strcmp(ArrayOfCourses[i].courseID, searchCourse))//if course found
    {//outputs
          found = 1;
          printf("------------------\n");
          printf("%s %.0f\n", ArrayOfCourses[i].courseName, ArrayOfCourses[i].totalCredit);
          for(int j = 0; j < amountEnrolls; j++)//nested loop to pull relevent information from corresponding (linked) arrays.
          {
            if(!strcmp(ArrayOfEnrollments[j].couID, ArrayOfCourses[i].courseID))
            {
              for(int t = 0; t < amountStudents; t++)
              {
                if(ArrayOfEnrollments[j].stuId == ArrayOfStudents[t].id)
                {
                  printf("%s %s %s %.0f %c\n", ArrayOfStudents[t].firstName, ArrayOfStudents[t].lastName, ArrayOfEnrollments[j].semester, ArrayOfEnrollments[j].score, calcGrade(ArrayOfEnrollments[j].score));
                }
              }
            }              
          }  
   }
  }
  if(found == 0)
  {
    printf("------------------\n");
    printf("not found\n");
  }  
  
  printf("------------------\n");
}
void search_courseSemester(Student ArrayOfStudents[], int amountStudents, Course ArrayOfCourses[], int amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls, char searchCourse[], char searchSemester[])//Searche for CourseId but within a specific semester
{
  int found = 0;
  for(int i = 0; i < amountCourses; i++)
  {
    if(!strcmp(ArrayOfCourses[i].courseID, searchCourse))
    {
          found = 1;
          printf("------------------\n");
          printf("%s %.0f\n", ArrayOfCourses[i].courseName, ArrayOfCourses[i].totalCredit);
          for(int j = 0; j < amountEnrolls; j++)
          {
            if(!strcmp(ArrayOfEnrollments[j].couID, ArrayOfCourses[i].courseID)&&!strcmp(ArrayOfEnrollments[j].semester, searchSemester))//Checks to see if the ID AND the semester match the search criteria
            {
              for(int t = 0; t < amountStudents; t++)
              {
                if(ArrayOfEnrollments[j].stuId == ArrayOfStudents[t].id)
                {
                  printf("%s %s %s %.0f %c\n", ArrayOfStudents[t].firstName, ArrayOfStudents[t].lastName, ArrayOfEnrollments[j].semester, ArrayOfEnrollments[j].score, calcGrade(ArrayOfEnrollments[j].score));
                }
              }
            }              
          }  
          printf("------------------\n");
    }
   }
   if(found == 0)
  {
    printf("------------------\n");
    printf("not found\n");
    printf("------------------\n");
  }
}
void count(Student ArrayOfStudents[], int amountStudents, Course ArrayOfCourses[], int amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls, int x){//Counts all students, either generally or by category by using a switchcase to figure out what category of counting will be used, and then incrementing counters to reflect the amount of students in this category.
  printf("------------------\n");
  switch(x)
  {
    case 1:
    {
      printf("total students %d\n", amountStudents);
      break;
    }
    case 2:
    {
      for(int i = 0, s = 0; i < amountCourses; i++)
      {
        s = 0;
        for(int e = 0; e < amountEnrolls; e++)
        {
          if(!strcmp(ArrayOfEnrollments[e].couID, ArrayOfCourses[i].courseID))
          {
            s++;
          }
        }
        printf("%s %d\n", ArrayOfCourses[i].courseID, s);
      }
      break;
    }
    case 3:
    {
      char semester[50], semester2[50];
      strcpy(semester, ArrayOfEnrollments[0].semester);
      int counters[2];
      int s1 = 0, s2 = 0,  i = 0;
      while(!strcmp(ArrayOfEnrollments[i].semester, semester)&&i<amountEnrolls)
        {
           s1++;
           i++;
        }
      strcpy(semester2, ArrayOfEnrollments[i].semester);        
      while(!strcmp(ArrayOfEnrollments[i].semester, semester2)&&i<amountEnrolls)
        {
          s2++;
          i++;
        }
      printf("%s %d\n%s %d\n",semester, s1, semester2, s2);
      break;
    }
  }
  printf("------------------\n");
}
void add_course(Course ArrayOfCourses[], int amountCourses, char cId[], char cName[], int credit){//Opens the courses.txt file and appends to it with the data inputted by the user to create a new course
  int i;
  for(i = 0; i < amountCourses; i++)
  {
    if(!strcmp(ArrayOfCourses[i].courseID, cId))
      break;
  }
  if(i == amountCourses)
  {
    FILE *out;
    out = fopen("courses.txt", "a");
    fprintf(out, "\n%s %s %d", cId, cName, credit);
    fclose(out);
    printf("------------------\n");
    printf("record added\n");
    printf("------------------\n");
  }
  else
  {
    printf("------------------\n");
    printf("\"violation of course id uniqueness. Cannot add the record.\"\n");
    printf("------------------\n");
  }
}
void swap(Student *x, Student *y)  //Swaps two students
{  
    Student temp = *x;  
    *x = *y;  
    *y = temp;  
} 
void sort(Student arrayOfStudents[], int amountStudents)  //sorts through the array of students by using a selection sort and the swap function
{  
    int i, j, min_idx;  
  
    for (i = 0; i < amountStudents-1; i++)  
    {  
        min_idx = i;  
        for (j = i + 1; j < amountStudents; j++)
        {
          if (arrayOfStudents[j].id < arrayOfStudents[min_idx].id)
          {
            min_idx = j;
          }
        }  
        
        swap(&arrayOfStudents[min_idx], &arrayOfStudents[i]);  
    }
    //outputs sorted student array (sorted by ID)
    printf("------------------\n");
    for (i = 0; i < amountStudents; i++)  
    {  
      printf("%d %s %s %d/%d/%d\n", arrayOfStudents[i].id, arrayOfStudents[i].firstName, arrayOfStudents[i].lastName, arrayOfStudents[i].monthOB, arrayOfStudents[i].dayOB, arrayOfStudents[i].yearOB);
    }
    printf("------------------\n");
} 
void menu(Student ArrayOfStudents[], int amountStudents, Course ArrayOfCourses[], int amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls){//menu that loops through the aforementioned functions given user input until user inputs the exit command. 
 
  char command[20];
  char subcommand[20];
  char input[50];

    printf("==================\n");
    scanf("%s", command);
    if(!strcmp(command, "search_students"))
    {
      scanf("%s", subcommand);
      if(!strcmp(subcommand, "lname"))
      {
        scanf("%s", input);
        search_student(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls, input, 1);

      }
      else if(!strcmp(subcommand, "fname"))
      {
        scanf("%s", input);
        search_student(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls, input, 2);
      }
      else if(!strcmp(subcommand, "id"))
      {
        scanf("%s", input);
        search_student(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls, input, 3);
      }
      else if(!strcmp(subcommand, "byear"))
      {
        scanf("%s", input);
        search_student(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls, input, 4);
      }
    }
    else if(!strcmp(command, "search_course"))
    {
      scanf("%s", subcommand);
      if(!strcmp(subcommand, "cId")||!strcmp(subcommand, "cid"))
      {
        scanf("%s", input);
        search_courseID(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls, input);
      }
      else if(!strcmp(subcommand, "cId_semester")||!strcmp(subcommand, "cid_semester"))
      {
        char input2[50];
        scanf("%s %s", input, input2);
        search_courseSemester(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls, input, input2);
      }
    }
    else if(!strcmp(command, "add_course"))
    {
      char cId[50];
      char cName[50];
      int credit;
      scanf("%s %s %d", cId, cName, &credit);
      add_course(ArrayOfCourses, amountCourses, cId, cName, credit);
    }
    else if(!strcmp(command, "count"))
    {
      scanf("%s", subcommand);
      if(!strcmp(subcommand, "students"))
      {
        count(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls, 1);
      }
      else if(!strcmp(subcommand,"students_course"))
      {
        count(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls, 2);
      }
      else if(!strcmp(subcommand, "students_semester"))
      {
        count(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls, 3);
      }
    }
      else if(!strcmp(command, "sort"))
      {
        sort(ArrayOfStudents, amountStudents);
      }
      else if(!strcmp(command, "exit"))
      {
        printf("------------------\n");
        printf("Bye!");  
        exit(1);
        free(ArrayOfCourses);
        free(ArrayOfStudents);
        free(ArrayOfEnrollments);
      }
    else ;
}
int main(void) {
  //creating and loading structures stud, cour, and enroll (students, courses, and enrollments)
  
  /*for(int i = 0; i < studSize; i++)
  {
    printf("%d %s %s %d %d %d\n", stud[i].id, stud[i].firstName, stud[i].lastName, stud[i].dayOB, stud[i].monthOB, stud[i].yearOB);
  }///for testing *stud
  printf("\n");
  for(int i = 0; i < courSize; i++)
  {
    printf("%s %s %f\n", cour[i].courseID, cour[i].courseName, cour[i].totalCredit);
  }///for testing *Course
  printf("\n");
  for(int i = 0; i < enrollSize; i++)
  {
    printf("%s %d %s %f\n", enroll[i].couID, enroll[i].stuId, enroll[i].semester, enroll[i].score);
  }//for testing *Course*/
    while(1)
  {
    int studSize = 0;
  Student *stud = loadStudent(&studSize);
  int courSize = 0;
  Course *cour = loadCourse(&courSize);
  int enrollSize = 0;
  Enrollments *enroll = loadEnroll(&enrollSize);
  menu(stud, studSize, cour, courSize, enroll, enrollSize);//call menu function
  }
  return 0;
}