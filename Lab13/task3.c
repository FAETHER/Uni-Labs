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


void sto_lower(char* in)
{
  while(*in)
    {
      *in = tolower(*in);
      in++;
    }
  *(in-1) = '\0';
}


char* alpha(char* in)
{
  char* new = (char*) malloc(fstrlen(in)+1);
  char* keep = new;
  memset(new, 0, fstrlen(in)+1);
  while(*in)
    {      
      if(isalpha(*in))
	{
	  *new = *in;
	  new++;
	}
      in++;
    }
  return keep;    
}

char is_palindrome(char* in)
{
  sto_lower(in);
  in = alpha(in);
  int len = fstrlen(in);
  char* end = in + len-1;
  while(*in)
    {
      //printf("%c\n", *in);
      //printf("%c\n", *end);
      if(*in != *end)
	{
	  return 0;
	}
      in++;
      end--;
    }
  return 1;
}

int main() 
{
  char t[] = "Nooon\n";
  printf("%d\n", is_palindrome(t));
  return 0; 
} 
