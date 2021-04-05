/* PLEASE DO NOT MODIFY A SINGLE STATEMENT IN THE TEXT BELOW.
READ THE FOLLOWING CAREFULLY AND FILL IN THE GAPS

I hereby declare that all the work that was required to 
solve the following problem including designing the algorithms
and writing the code below, is solely my own and that I received
no help in creating this solution and I have not discussed my solution 
with anybody. I affirm that I have read and understood
the Senate Policy on Academic honesty at 
https://secretariat-policies.info.yorku.ca/policies/academic-honesty-senate-policy-on/
and I am well aware of the seriousness of the matter and the penalties that I will face as a 
result of committing plagiarism in this assignment.

BY FILLING THE GAPS,YOU ARE SIGNING THE ABOVE STATEMENTS.

Full Name: Laura Toro
Student Number: 216650236
Course Section: M
eecs user id: lttoro20

*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 30
#define fieldLength 200


#define diskFile "diskFile.dat"
#define courseFile "course.txt"

struct db_type
{
   char name[fieldLength];
   int age;
   char course1[fieldLength];
   char course2[fieldLength];
   char status[fieldLength];
 };

struct courseInfo
{ 
  char code [20]; // e.g., EECS2030
  char title [fieldLength];
  char  date [20];
  char time_start [20];
  char time_end [20];
  char  location [20]; 
};
 
 
struct courseInfo courseArr[SIZE]; // global variable  courseArr of struc
     

char prompt_menu(void);
void init_list(struct db_type * pArr[]); 
void clearDB(struct db_type * pArr[]);
void init_courseArr(void);

void writeDisk(struct db_type * pArr[]); 
void emptyDisk(void); 
void loadDisk(struct db_type * pArr[]); 





int main(int argc, char *argv[])
{
    
    struct db_type * db_pArr[SIZE];  // main db storage



    init_list(db_pArr);  // set to NULL
    
    init_courseArr();  // load course from diskfile
    
    char choice;
    for(; ;){
      choice = prompt_menu();
      switch (choice)
      {
         case 'n': enterNew(db_pArr); break;
         case 'd': displayDB(db_pArr); break;
         case 'w': writeDisk(db_pArr);  break;    
         case 'l': loadDisk(db_pArr); break;
         case 's': sort(db_pArr); break;
	   
         case 'c': clearDB(db_pArr); break;  
         case 'e': emptyDisk();break;

         case 'v': displayCourses();break;
         case 'p': swap(db_pArr); break;
         case 'r': removeRecord(db_pArr);break;
         
         case 'q': exit(1); // terminate the whole program
       }
	
     }
     return 0;
}

void init_list(struct db_type * pArr[]){
  int t;
  for (t=0; t<SIZE; t++)
  { 
     pArr[t]= NULL;
  }
}

void clearDB(struct db_type * pArr[]){
   char c3[3];
   printf("are you sure to clear db? (y) or (n)? ");
 
   fgets(c3,3,stdin);
   
   if(! strcmp(c3, "y\n"))  
      init_list(pArr);
}


char prompt_menu(void){
  char s[80];
  while(1){
    printf("\n-----------------------------------------------------------------\n");
    printf("|    %-20s","(N)ew record");
    printf("%-20s","(R)emove record");
    printf("Swa(p) records\t|\n");
    printf("|    %-20s","(S)ort database");
    printf("%-20s","(C)lear database");
    printf("(D)isplay db\t|\n");
  
    printf("|    %-20s","(L)oad disk");
    printf("%-20s","(W)rite disk");
    printf("(E)mpty disk\t|\n");
  
    printf("|    %-20s", "(V)iew courses");//|\tSwa(p) record\t(Q)uit\t\t\t\t|\n");
    printf("%-20s","(Q)uit");
    printf("*Case Insensitive*\t|\n");
    printf("-----------------------------------------------------------------\n");
    printf("choose one: ");
  
    fgets(s,50, stdin); // \n added
   
    if (strlen(s) == 2 && strchr("edlsuqrcwnvpr", tolower(*s))) 
       return tolower(*s); // s[0], return the first character of s  
    //else
    printf("not a valid input!\n");
	 
 }
}

/* display all or specified course */
void displayCourses(void){   
   char string[80];
   char a[] = {'a', '\0'};
   int found = 0;

  printf("course code (or 'a')? ");
  fgets(string, 80, stdin);
  string[strlen(string)-1] = '\0';

 // printf("studenting %s, %s \n",  a, string);

/* if(strcmp(string, a ) == 0 ){
  printf("student");
} else {
  printf("student2");
} */

  if(strcmp(string, a ) == 0 )  {
    printf("=================================================================================\n");
    for(int i = 0; i <  21  ; i++){
      printf("%s\t%-40s%-5s %s-%s   %s\n", courseArr[i].code, courseArr[i].title, courseArr[i].date, courseArr[i].time_start, courseArr[i].time_end, courseArr[i].location);
    }
   
  printf("=================================================================================\n");  // the provide PE2.out uses "%s\t%-40s%-5s %s-%s   %s\n" as formatting string for printing each course info
  
  } else if(strlen(string) < 5) {
    char *numbersOnly;

    for(int m = 0; m <21; m++){
      if (numbersOnly = strstr(courseArr[m].code, string)){
        printf("%s\t%-40s%-5s %s-%s   %s\n", courseArr[m].code, courseArr[m].title, courseArr[m].date, courseArr[m].time_start, courseArr[m].time_end, courseArr[m].location);
        found = 1;
        break;
      } 
    }

      if (found == 0){
      printf("error! course does not exist");
      }


  } else {


    for(int j = 0; j < 21; j++ ){
      if(strcmp(string, courseArr[j].code ) == 0 ){
        printf("%s\t%-40s%-5s %s-%s   %s\n", courseArr[j].code, courseArr[j].title, courseArr[j].date, courseArr[j].time_start, courseArr[j].time_end, courseArr[j].location);
       found = 1;
       break;
      }
    }
      if (found == 0){
      printf("error! course does not exist");
      }
    }

  } 




/* input items into the list */
void enterNew(struct db_type * pArr[SIZE]){  

  char name[fieldLength];
  int age[3];
  char course1[fieldLength];
  char course2[fieldLength];
  char status[fieldLength];

  
  printf("name: ");
  fgets(name, fieldLength, stdin);
  name[strlen(name)-1] = '\0';

  printf("age: ");
  fgets(age, 3, stdin);
 
  

  printf("course-1: ");
  fgets(course1, fieldLength, stdin);
  course1[strlen(course1)-1] = '\0';
  // printf("%d", isValid(course1));


  

  while(isValid(course1) == 0){
    
    printf("course does not exist, enter again: ");
    fgets(course1, fieldLength, stdin);
      course1[strlen(course1)-1] = '\0';
    
    } 
  
    char compareStartTime1[20];
    char compareEndTime1[20];

      for(int i =0; i <21; i ++){
      if( (strcmp(course1, courseArr[i].code ) == 0) || /* numbersOnly = */  (strstr(courseArr[i].code, course1)) ){
      strcpy(compareStartTime1, courseArr[i].time_start);
      strcpy(compareEndTime1, courseArr[i].time_end);
      // printf("test compare 1\n");
      break;
      
    }
   }

  
//helper function used to check
//for int i = 0; i++
//if course1 == courses[i].code
//isValid == 0;
//if isValid == 0
//printf("try again");
//fgets(course1, fieldLength, stdin);

  printf("course-2: ");
  fgets(course2, fieldLength, stdin);
  course2[strlen(course2)-1] = '\0';


  while(isValid(course2) == 0){
    
    printf("course does not exist, enter again: ");
    fgets(course2, fieldLength, stdin);
      course2[strlen(course2)-1] = '\0';
    
    } 

    char compareStartTime2[20];
    char compareEndTime2[20];

      for(int i =0; i <21; i ++){
      if( (strcmp(course2, courseArr[i].code ) == 0) || /* numbersOnly = */  (strstr(courseArr[i].code, course2)) ){
      strcpy(compareStartTime2, courseArr[i].time_start);
      strcpy(compareEndTime2, courseArr[i].time_end);
      // printf("test compare\n");
      break;
      
    }
   }
  


  // loop check if array at i is empty then add
  //new element 

struct db_type student[SIZE];
strcpy(student->name, name);
student->age = age;
strcpy(student->course1, course1);
strcpy(student->course2, course2);


//compare times overlapping
 if(compareStartTime1 <= compareEndTime2 && compareEndTime1 >= compareStartTime2){
  strcpy(student->status, "ATTENTION! time conflict");

  printf("ATTENTION! time conflict");
} else {
  strcpy(student->status, "SUCCESSFUL! no time conflict");
  printf("SUCCESSFUL! no time conflict");

} 


int counter; 
for(counter = 0; counter < SIZE; counter++){
  if(pArr[counter] == NULL){
    // printf("test\n");
    pArr[counter] = student;
    
     //printf("%s\n", pArr[counter]->status);

    
    // printf("%d\n", pArr[counter]->age);

    
    // printf("%s\n",pArr[counter]->course1);

    
    // printf("%s\n", pArr[counter]->course2);
    break;
  }
} 






// printf("reached end");

}

 int isValid(char course[fieldLength]){
   int isValid = 0;
   // char *numbersOnly;
   for(int i =0; i <21; i ++){
      if( (strcmp(course, courseArr[i].code ) == 0) || /* numbersOnly = */  (strstr(courseArr[i].code, course))){
      isValid = 1;
      break;
      
    }
   }
  return isValid;
} 
   



/* display records */
void displayDB(struct db_type * pArr[]){
  ;
 
}


/* remove an existing item */
void removeRecord (struct db_type * pArr[])	
{
  ;

}

/* swap records */
void swap(struct db_type * pArr[]){
   
	; 
} 

/* load from course.txt, store into (global) courseArr of courses  */
void init_courseArr(void){ 
 
   FILE *fr; //file pointer
   fr = fopen (courseFile, "r");
   char arr[50];  
   int count = 0;
   while ((fgets(arr,100,fr)) != NULL)
   {  
     strncpy(courseArr[count].code,  arr, strlen(arr)-1); // remove \n  
     courseArr[count].code[strlen(arr)-1] = '\0';  //to be safe
	 
     fgets(arr,100,fr);  
     strncpy(courseArr[count].title ,  arr, strlen(arr)-1);
     courseArr[count].title[strlen(arr)-1] = '\0';  //to be safe
     
          
     fgets(arr,100,fr); 
     strncpy(courseArr[count].date,  arr, strlen(arr)-1);
     courseArr[count].date[strlen(arr)-1] = '\0';  //to be safe
	   
     // other ways, remove \n before
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].time_start,  arr);
      
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].time_end,  arr);
      
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].location,  arr); 
	  
     count++;
     fgets(arr,100,fr); // read the empty line
   }

   strcpy(courseArr[count].code, "EECS0000"); // a terminator token structure

   fclose(fr);
	 
 }
    
/************************ DISK IO *****************************************************************/

void writeDisk(struct db_type * pArr[]){
  FILE *fp;
  int i;

  if ( (fp=fopen(diskFile,"ab")) == NULL)
  {
    printf("cannot open file\n");
    return;
  }

  
  for (i=0; i< SIZE ; i++)
  {
     if ( pArr[i] != NULL)
     {  
       if (fwrite( pArr[i], sizeof(struct db_type), 1, fp) != 1)
       { 
          printf("file write error\n");
       }
     } 
   }
   fclose(fp);

}

void emptyDisk(void){

  FILE *fp;
  
  char c3[3];
  printf("are you sure to empty disk? (y) or (n)? ");
  fgets(c3,3,stdin);
  if(strcmp(c3, "y\n"))  
     return;
 
  //else
  if ( (fp = fopen(diskFile,"w")) == NULL)
  {
     printf("no file to open\n");
     return;
  }
  fclose(fp); // open close, will empty the file
}


void loadDisk(struct db_type * pArr[]){
  FILE *fp;
  int i;
  char c3[3];
  printf("will overwrite current records. are you sure to load disk? (y) or (n)? ");
  fgets(c3,3,stdin);
  if(strcmp(c3, "y\n"))  
     return;

  struct db_type * tmp;  
  
  if ( (fp = fopen(diskFile,"r")) == NULL)
  {
    printf("cannot open file\n");
    return;
  }

  init_list(pArr);
  for (i=0; i < SIZE ; i++)
  {    
     
     tmp =  (struct db_type *) malloc (sizeof(struct db_type));   
	   
     if (fread( tmp, sizeof(struct db_type), 1, fp) != 1)
     {
       if (feof(fp))
       { fclose(fp); 
         return;
       }
       printf("file read error\n");
     }
     else pArr[i] = tmp;
  }
}

/****bonus*************************************************************************************/

/* sort the records by ages */
void sort(struct db_type * pArr[])
{
 

}  

 
 
