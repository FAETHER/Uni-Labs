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
int a = 2;
 int b = 2;
 int x = a++;
 int y = ++b;
 printf("a = %d\n", a);
 printf("b = %d\n", b);
 printf("x = %d\n", x);
 printf("y = %d\n", y);  
}
