// Example program

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

int largeNum(int* arr, int size)
{
  int max = *arr;
  for (int i = 0; i < size; i++)
    {
    for (int j = 0; j < size; j++)
      {
	printf("%d \n", *((arr+i*size) + j));
	if(*((arr+i*size) + j) > max)
	  {
	    max = *((arr+i*size) + j);
	  }
      }

    }
    
  return max;
}

void sumcols(int* arr, int size)
{
  int sum[size];
  memset(sum, 0, sizeof(int)*size);

  for (int i = 0; i < size; i++)
    {
    for (int j = 0; j < size; j++)
      {
        sum[i] += *((arr+i*size) + j);
      }
    }

  for(int z = 0; z<size; z++)
    {
      printf("Sumcols: %d\n", sum[z]);
    }
  return;
}

int main()
{
  int arr[3][3];
  for(int x = 0; x<3; x++)
    {
      for(int y = 0; y<3; y++)
      {       
	arr[x][y] = rand() % 10;
      }
    }

  printf("Max is: %d\n", largeNum((int*)arr, 3));
  sumcols((int*) arr, 3);
  
}
