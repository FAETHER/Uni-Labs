// Example program

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "math.h"
#include <setjmp.h>

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

int main()
{
  char* abc = "heLLo\n";

  /* while(abc) */
  /*   { */
      
  /*     abc++; */
  /*   } */
  
  for(int i = 0; i<fstrlen(abc); i++)
  {
    if(abc[i] < 0x61)
      {
	printf("%c\n", abc[i]);
	break;
      }
  }

}

/* Task 3: */
/* The number stored would be 4 */

/* Task 4: */
/* It would print now working */
