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

typedef struct
{
  char name[20];
  char extension[5];
  int file_size;
}file_t;

int main() 
{

  int n = 980765;
  
  char str[100]; // todo: normally we would want to know the dynamic context.
  memset(str, 0, sizeof(str)); //no need for garbage memory.
  int line = 0; //count lines in file
  int len;
  char weird_skip = 1;
  int next = 0;

  file_t* p;
  int nn = 98067;
  file_t* ps;
  
  while(fgets(str, 100, stdin) && (line) != n)
    {
      if(weird_skip)
	{
	  weird_skip = 0;
	  n = atoi(&str[0]);
	  nn = atoi(&str[2]);	  
	  p = (file_t*) calloc(n, sizeof(file_t)); //allocate the bi* on stack
	  ps = p;
	  continue;
	}

      if(line == (n-1) && n != nn)
	{
	  int dif = ps - p;
	  p = (file_t*) realloc(ps, nn*sizeof(file_t));
	  for(int i = 0; i<line; i++)
	    {
	      p ++;
	    }
	  //ps = p;
	  n = nn;
	}
            
      len = fstrlen(str);
      next = sstrlen(str);
      memcpy(p->name, str, next);
      memcpy(p->extension, &str[next+1], sstrlen(&str[next+1]));
      next += sstrlen(&str[next+1]);
      p->file_size = atoi(&str[next+1]);
      p++;
      line++;
    }

  for(int i = 0; i<nn; i++)
    {
      //printf("%p\n", ss[i]);
      printf("%s.%s, %d bytes\n", ps[i].name, ps[i].extension, ps[i].file_size);
      //free(ss[i]);
    }

  /* free(ss); */
  
  
  return 0; 
} 
