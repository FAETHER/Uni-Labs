// Example program

#include <stdio.h>
#include <stdlib.h>
#include "math.h"

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

int GCD(int a, int b)
{
  while (a % 2 == 0 && b % 2 == 0)
    {
      a = a/2;
      b = b/2;
      ret++;
    }
  while(a != b)
    {
      if(a % 2 == 0)
	{
	  a = a/2;
	}
      else if(b % 2 == 0)
	{
	  b = b/2;
	}
      else if(a > b)
	{
	  a = (a-b)/2;
	}
      else
	{
	  b = (b-a)/2;
	}
    }
  return a;
}

int main()
{
  printf("%d\n", GCD(10, 25));
}
