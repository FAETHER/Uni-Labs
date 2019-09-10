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

jmp_buf buf;

void swaparr(int* a, int* b, int size)
{  
  for(int i = 0; i<size; i++)
    {
      int tmp = a[i];
      a[i] = b[i];
      b[i] = tmp;
    }
  longjmp(buf, 1);
}

int main()
{
  int len;
  scanf ("%d",&len);
  
  int ints[len];
  int _ints[len];
  
  for(int i = 0; i<len; i++)
    {
      scanf("%d", &ints[i]);
    }

  for(int i = 0; i<len; i++)
    {
      scanf("%d", &_ints[i]);
    }

  int val = setjmp(buf);
  if(val == 1)
    goto s;
  swaparr(&ints[0], &_ints[0], len);
 s:;

  for(int i = 0; i<len; i++)
    {
      printf("%d", ints[i]);
    }

  printf("\n");

  for(int i = 0; i<len; i++)
    {
      printf("%d", _ints[i]);
    }

  printf("\n");
    
}
