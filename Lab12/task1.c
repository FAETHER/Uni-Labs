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

void swap_chars(char* in)
{
  while(*in)
    {
      if(*in < 'a')
	{
	  *in |= 32;
	}
      else
	{
	  *in ^= 32;
	}
      in++;
    }
  *(in-1) = '\0';
}

int main() 
{

  char t[] = "BHBgjjhg\n";

  swap_chars(t);

  printf("%s\n", t);
  
  return 0; 
} 
