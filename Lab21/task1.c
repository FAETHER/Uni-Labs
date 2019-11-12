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
  for(; head != NULL;)
    {
      printf(" %c\n", head->c);
      head = head->next;
    }
  head = org;
}

void add_n(char c)
{
  node_t* org = head;
  for(; head != NULL; )
    {
      if(head->next == NULL)
	{
	  head->next = (node_t*) calloc(LEN, sizeof(node_t));
	  head->next->c = c;
	  break;
	}
      head = head->next;
    }
  head = org;  
}

void add_first(node_t** head, node_t new_item)
{
  node_t* org = *head;
  *head = (node_t*) calloc(1, sizeof(node_t));
  (*head)->c = new_item.c;
  (*head)->next = org->next;
  return;
}

int insert_node(node_t** head, char new_item, int index)
{
  node_t* org = *head;
  node_t* prev;
  int i;
    for(i = 0; *head != NULL && i<index; i++)
      {
	if(i == index-1)
	  {
	    prev = *head;
	  }
	*head = (*head)->next;
      }
    prev->next = (node_t*) calloc(1, sizeof(node_t));
    prev->next->c = new_item;
    prev->next->next = *head;

    //    printf("%d %d\n", i, index);
    ASSERT(i == index, "err, index != i");

    *head = org;
    
    return 1;
}

int main() 
{
  head = (node_t*) calloc(1, sizeof(node_t));
  head->c = 'A';
  head->next = (node_t*) calloc(1, sizeof(node_t));
  head->next->c = 'B';
  // head->next->next = (node_t*) calloc(1, sizeof(node_t));
  // no need to set to null as calloc did that already.

  add_n('C');
  add_n('D');
  
  print_list();

  node_t new;
  new.c = 'T';
  new.next = NULL;
  add_first(&head, new);

  printf("\n");
  
  print_list();

  insert_node(&head, 'N', 2);
  
  printf("\n");
  
  print_list();

  
  
  
  return 0; 
} 
