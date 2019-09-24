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

typedef struct point_t
{
  double x;
  double y;
}point_t;

double distance(point_t a, point_t b )
{
  return sqrtf(powf((b.x - a.x), 2) + powf(b.y - a.y, 2));
}

void print(point_t p)
{
  printf("(lf%, lf%)", p.x, p.y);
}

//this code is so simple that I do not even need to test run it.

int main()
{

}
