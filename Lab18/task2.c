// Example program
#include "header.h"

size_t fstrlen (const char* s) 
{
	register const char* i;
	for(i=s; *i; ++i);
	return (i-s);
}

size_t sstrlen (const char* s) 
{
	register const char* i;
	for(i=s; *i != ' '; ++i);
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

char* xor_encrypt(char* s, char key)
{
  int len = fstrlen(s)+1;
  char* ns = (char*) malloc(len);
  memcpy(ns, s, len);
  s = ns;
  while(*ns)
    {
      *ns = *ns ^ key;
      ns++;
    }  
  *(ns-1) = '\0';

  return s;
}

int main() 
{
  char* s = xor_encrypt("BYE WORLD", 20);
  printf("%s\n", s);
  
  return 0; 
} 
