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

int count_inst(int num, int* arr, int size)
{
  if(*((uint8_t*)arr+(size * sizeof(int))) == (char)num)
    {
      //printf("ggg\n");
      *((uint8_t*)&num+3) += 1;
    }
  if(size == 0)
    {
      return *((uint8_t*)&num+3);
    }
  count_inst(num, arr, size-1);
}

int main()
{
  int arr[8] = {1, 50, 3, 4, 5, 7, 5, 10};
  printf("%d\n", count_inst(5, arr, 8));
}
