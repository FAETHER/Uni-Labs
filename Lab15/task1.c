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

  file_t** ss;
  
  while(fgets(str, 100, stdin) && (line) != n)
    {
      if(weird_skip)
	{
	  weird_skip = 0;
	  n = ((str[0] - '0'));
	  ss = (file_t**) calloc(n, sizeof(file_t*)); //allocate the bi* on stack
	  //ss = s;
	  continue;
	}
	
      len = fstrlen(str);

      file_t* p = (file_t*) calloc(1, sizeof(file_t)); //allocate in a loop because I do not care.

      next = sstrlen(str);
      memcpy(p->name, str, next);
      memcpy(p->extension, &str[next+1], sstrlen(&str[next+1]));
      next += sstrlen(&str[next+1]);
      p->file_size = atoi(&str[next+1]);
      ss[line] = p;
      //printf("%s\n", &str[next]);
      
      line++;
    }

  for(int i = 0; i<n; i++)
    {
      //printf("%p\n", ss[i]);
      printf("%s.%s, %d bytes\n", ss[i]->name, ss[i]->extension, ss[i]->file_size);
    }
  
  
  return 0; 
} 
