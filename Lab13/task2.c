// Example program

#include "header.h"

size_t fstrlen (const char* s) 
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

char* alpha(char* in)
{
  char* new = (char*) malloc(fstrlen(in)+1);
  char* keep = new;
  memset(new, 0, fstrlen(in)+1);
  while(*in)
    {      
      if(isalpha(*in))
	{
	  //printf("Here\n");
	  *new = *in;
	  new++;
	}
      in++;
    }
  return keep;    
}

int main() 
{
  char t[] = "Hello, world!\n";

  char* tt = alpha(t);

  printf("%s\n", tt);
  
  return 0; 
} 
