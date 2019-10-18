// Example program

#include "header.h"

size_t fstrlen (const char* s) 
{
	register const char* i;
	for(i=s; *i; ++i);
	return (i-s);
}


#define DEBUG
#ifdef DEBUG
#   define ASSERT(condition, message) \
    do { \
        if (! (condition)) \
		{ \
			printf("%s \n", message);\
			printf("Assertion %s failed in, %s line: %d \n", #condition, __FILE__, __LINE__);\
			char buf[10];					\
			fgets(buf, 10, stdin); \
			exit(1); \
        } \
    } while (0)
#else
#   define ASSERT(condition, message) do { } while (0)
#endif

typedef struct {char course_name[25];double* quiz_grades;double average;} course_t;
typedef struct {char student_name[25];course_t* courses;double gpa;} student_t;

typedef struct {char student_name[25]; char id[25]; char major[25];} swag_t;


int main() 
{

  int n = 980765;
  
  student_t* p ;
  student_t* rover;
  course_t* addr;
  
  char str[100]; // todo: normally we would want to know the dynamic context.
  memset(str, 0, sizeof(str)); //no need for garbage memory.
  int line = 0; //count lines in file
  int len;
  char weird_skip = 1;
  int next = 0;
  int offs = 0;
  
  while(fgets(str, 100, stdin) && (line+1) != n)
    {
      if(weird_skip)
	{
	  weird_skip = 0;
	  n = ((str[0] - '0') * 3);
	  p = (student_t*) calloc(n,sizeof(student_t));
	  addr = (course_t*) calloc(3*n,sizeof(course_t)); //3 courses per student
	  for(int i = 0; i<n; i++)
	    {
	      (p+(i*sizeof(student_t)))->courses = (addr+(i*sizeof(course_t)*3));
	      for(int z = 0; z<3; z++)
		{
		  course_t* tmp = (p+(i*sizeof(student_t)))->courses+(z*sizeof(course_t));
		  tmp->quiz_grades = (double*) calloc(10, sizeof(double)); //assume to be 10 at most
		}
	    }
	  rover = p;
	  continue;
	}
	
      len = fstrlen(str);

      if(line % 7 == 0)
	{
	  memcpy(p->student_name, str, len);
	  if(next != 0)
	    {
	      course_t* ptr = p->courses+(offs);
	      double sum = 0;
	      while(ptr->average)
		{
		  sum += ptr->average;
		  ptr += sizeof(course_t);
		}
	      p->gpa = sum;
	      p += sizeof(student_t);
	    }
	  next = 1;
	}
      else if(next == 1)
	{
	  course_t* ptr = p->courses+(offs);
	  memcpy(ptr->course_name, str, len);
	  next = 2;
	}
      else if(next == 2)
	{
	  int c = 0;
	  course_t* ptr = p->courses+(offs);
	  double avg = 0;
	  for(int z = 0; z<len; z++)
	    {
	      if(str[z] == ' ' || c == 0)
		{
		  str[z] = 't';		  
		  double* pp = ptr->quiz_grades+(c*sizeof(double));
		  *pp = atof(&str[z]);
		  avg += *pp;
		  c++;
		}
	    }
	  ptr->average = avg/c;
	  offs += sizeof(course_t);
	  next = 1;
	}
      
      line++;
    }

  /* for(int i = 0; i<n/3; i++) */
  /*   { */
  /*     printf("name %s\n", (rover+(i*sizeof(swag_t)))->student_name); */
  /*     printf("id %s\n", (rover+(i*sizeof(swag_t)))->id); */
  /*     printf("major %s\n", (rover+(i*sizeof(swag_t)))->major); */
  /*   } */
  
  
  return 0; 
} 
