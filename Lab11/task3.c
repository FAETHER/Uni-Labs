// Example program

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
      printf("org %d\n", arr[i]);
    }

  int* arrr = task3(arr, len);

  for(int i = 0; i<len; i++)
    {
      printf("post: %d\n", arrr[i]);
    }  
  
  return 0; 
} 
