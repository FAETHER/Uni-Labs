// Example program



//Lab 1 was read 10 strings from a test file and print them out.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main()
{
  char p[20];
  memset(p, 0x20, sizeof(p));


  for(int i = 10; i>0; i--)
    {
      p[i] = '*';
      p[15] = 0;
      printf("%s\n", p);
      i--;
    }
}
