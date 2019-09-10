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

char ifsorted(int* arr, int size)
{
  for(int i = 1; i<size; i++)
    {
      if(arr[i] < arr[i-1])
	{
	  return 0;
	}
    }
  return 1;
}

void insert(int val, int* arr, int size)
{
  ASSERT(ifsorted(arr,size), "Array is not sorted!");

  int new[size+1];
  memset(new, 0, sizeof(new));
  int placed = 0;
  
  for(int i = 0; i<size; i++)
    {
      if(arr[i] > val && !placed)
	{
	  new[i] = val;
	  new[i+1] = arr[i];
	  placed = 1;
	}
      else
	{
	  new[i+placed] = arr[i];
	}
    }

  if(!placed)
    {
      new[size] = val;
    }

    for(int i = 0; i<size+1; i++)
    {
      printf("%d", new[i]);
    }
  
}

int main()
{
  int len;
  scanf ("%d",&len);
  
  int ints[len];
  
  for(int i = 0; i<len; i++)
    {
      scanf("%d", &ints[i]);
    }

  int val = 6;
  insert(val, ints, len);

  
}
