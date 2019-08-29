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

void Double(int* arr, int size)
{
  for(int i = 0; i<size; i++)
    {
      arr[i] = arr[i] << 1;
    }
}

int main()
{
  int arr[5] = {21, 24, 3, 2, 8};
  Double(arr, 5);

  for(int i = 0; i<5; i++)
    {
      printf("%d\n", arr[i]);
    }	 
  
}
