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
  
  swag_t* p ;
  swag_t* rover;
  
  char str[100]; // todo: normally we would want to know the dynamic context.
  memset(str, 0, sizeof(str)); //no need for garbage memory.
  int line = 0; //count lines in file
  int len;
  char weird_skip = 1;
  int next = 0;

  
  while(fgets(str, 100, stdin) && (line+1) != n)
    {
      if(weird_skip)
	{
	  weird_skip = 0;
	  n = ((str[0] - '0') * 3);
	  p = (swag_t*) calloc(n,sizeof(swag_t));
	  rover = p;
	  continue;
	}
	
      len = fstrlen(str);

      if(line % 3 == 0)
	{
	  memcpy(p->student_name, str, len);
	  next = 1;
	}
      else if(next == 1)
	{	  
	  memcpy(p->id, str, len);
	  next = 0;
	}
      else
	{
	  memcpy(p->major, str, len);
	  p += sizeof(swag_t);
	}
      
      line++;
    }

  for(int i = 0; i<n/3; i++)
    {
      printf("name %s\n", (rover+(i*sizeof(swag_t)))->student_name);
      printf("id %s\n", (rover+(i*sizeof(swag_t)))->id);
      printf("major %s\n", (rover+(i*sizeof(swag_t)))->major);
    }
  
  
  return 0; 
} 
