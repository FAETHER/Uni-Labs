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

int to_decimal(char my_binary[])
{
  int result = 0;
  for(int i = 0; my_binary[i+1] != '\0'; i++)
    {
      if(!(my_binary[i] - '0'))
	{
	  continue;
	}
      else
	{
	  result = pow(2, i) + result;
	  //printf("%d\n", result);
	}
    }
  return result;
}

int main()
{
  char buf[200];
  fgets(buf, 200, stdin);

  printf("%d\n", to_decimal(buf));

  
}
