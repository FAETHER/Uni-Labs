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

struct a
{
  char st[100+1];
  char ct[100+1];
  char s[2+1];
  char zip[5+1];
};

int main()
{
  struct a abc;
  fgets(abc.st, 100, stdin);
  fgets(abc.ct, 100, stdin);
  fgets(abc.s, 2, stdin);
  fgets(abc.zip, 5, stdin);

  printf("%s\n", abc.st);
  printf("%s, %s %s\n", abc.ct, abc.s, abc.zip);  

}
