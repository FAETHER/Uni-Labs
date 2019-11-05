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

#define LEN 10

typedef struct node_t
{
  char c;
  struct node_t* next;
}node_t;

node_t* head = NULL;


void print_list()
{
  node_t* org = head;
  for(; head->next != NULL; head++)
    {
      printf("%c\n", head->c);
    }
  head = org;
}

void add_n(char c)
{
  node_t* org = head;
  for(; ; head++)
    {
      if(head->next == NULL)
	{
	  head->c = c;
	  head->next = (head+1);
	  break;
	}
    }
  head = org;  
}

int main() 
{
  head = (node_t*) calloc(LEN, sizeof(node_t));
  head->c = 'A';
  head->next = (head + 1);
  head->next->c = 'B';
  head->next->next = (head + 1);
  // no need to set to null as calloc did that already.

  add_n('C');
  add_n('D');

  print_list();

  char str[100];
  while(fgets(str, 100, stdin))
    {
      if(str[0] != '*')
	{
	  add_n(str[0]);
	  print_list();
	}
    }
  
  return 0; 
} 
