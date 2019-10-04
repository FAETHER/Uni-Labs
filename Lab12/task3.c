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

uint32_t count_trail_z(int in)
{
  int count = 0;
  char op;
  for(int i = 0; i<sizeof(int); i++)
    {
      char byte = *((char*)&in+i);
      while(byte)
	{
	  op = byte;
	  byte >>=1;
	  if((byte << 1) == op)
	    {
	      count++;
	    }
	  else
	    {
	      break;
	    }
	}
    }
  return count;
}

int main() 
{
  printf("%d\n", count_trail_z(12));
  printf("%d\n", count_trail_z(71));
  return 0; 
} 
