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

typedef struct square_t
{
  point_t p;
  int len;
}square_t;

typedef struct circle_t
{
  point_t p;
  int rad;
}circle_t;

typedef union dun_t
{
  square_t s;
  circle_t c;
}dun_t;

typedef struct shape_t
{
  int num;
  dun_t d;
}shape_t;

double area(shape_t* p)
{
  if(p->num)
    {
      return M_PI * pow(p->d.c.rad, 2); //circle
    }
  else
    {
      return p->d.s.len * p->d.s.len;
    }
  return 0.0f;
}

int main()
{
  int i;
  scanf("%d", &i);

  int l;
  scanf("%d", &l);

  shape_t inst;
  inst.num=i;
  inst.d.s.len = l;

  printf("Area of: %lf\n", area(&inst));
  
}
