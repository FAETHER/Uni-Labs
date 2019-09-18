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

char isPrime(int num)
{
  for(int i = 2; i<num/2; i++)
    {
      if(num % i == 0)
	{
	  return 0;
	}
    }
  return 1;
}


char isPrime_rec(int num, int i)
{

  if(num % i == 0)
    {
      return 0;
    }
  else if(i >= num/2)
    {
      return 1;
    }
  isPrime_rec(num, i+1);
}




int main()
{
  printf("%d\n", isPrime_rec(29, 2));
}
