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

typedef struct a
{
  char name[20+1];
  char brand[50+1];
  int units;
  double price;
}a;

void inc(a* p)
{
  p->units *= 2;
  p->price = (p->price * 20) / 100;
  return;
}

int main()
{
  struct a abc;
  fgets(abc.name, 20, stdin);
  fgets(abc.brand, 50, stdin);

  scanf("%d", &abc.units);
  scanf("%lf", &abc.price);

  inc(&abc);
  
  printf("%s\n", abc.name);
  printf("%s\n", abc.brand);
  printf("%d\n", abc.units);
  printf("%lf\n", abc.price);
  

}
