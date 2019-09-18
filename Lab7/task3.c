// Example program

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "math.h"
#include <setjmp.h>

inline size_t fstrlen (const char* s) 
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

struct runner
{
  char name[50];
  int km[3];
  double time[3];
};

int main()
{
  setbuf(stdout, NULL);
  
  int len;
  printf("Number of people:");  
  scanf("%d", &len);

  struct runner a[len];
  int i;
  for(i = 0; i<len; i++)
    {
      printf("Name:");
      scanf("%s", &a[i].name);
      for(int z = 0; z<3; z++)
	{
	  printf("km:");
	  scanf("%d", &a[i].km[z]);
	  printf("time:");	  
	  scanf("%lf", &a[i].time[z]);
	}
    }

  for(i = 0; i<len; i++)
    {
      printf("Name: %s\n", a[i].name);
      for(int z = 0; z<3; z++)
	{
	  printf("%d st run: %lf\n", z+1, (double)a[i].km[z]/a[i].time[z]);
	}      
    }

  
  
  
}
