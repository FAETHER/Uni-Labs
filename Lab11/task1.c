// Example program

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "math.h"
#include <setjmp.h>
#include "time.h"

#include "header.h"

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
  srand(time(0));
  
  int len = rand() % 20 + 1;
  int arr[len];
  for(int i = 0; i<len; i++)
    {
      arr[i] = rand() % 30 + 1;
    }

  printf("%d\n", max(arr, len));
  printf("%d\n", min(arr, len));
  
  return 0; 
} 
