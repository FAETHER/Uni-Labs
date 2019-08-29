// Example program

#include <stdio.h>
#include <stdlib.h>
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
  char in;
  scanf (" %c",&in);
  
  int arr[2];
  switch(in)
    {
    case 'T':
      //printf("here\n");
      for(int i = 0; i<2; i++)
	{
	  scanf("%d", &arr[i]);
	}
      printf("area of triangle: %f\n", (double) (arr[0]*arr[1]) / 2);
	break;
    case 'C':
	  scanf("%d", &arr[0]);
	  printf("Area of cicle: %.4lf\n", (double)3.14*(arr[0]*arr[0]));
	break;
    case 'S':
	  scanf("%d", &arr[0]);
	  printf("Area of square: %d\n", (arr[0]*arr[0]));      
	break;
      

    }

}
