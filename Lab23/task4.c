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

// A linked list node  
struct Node {  
    int data;  
    struct Node* next;  
    struct Node* prev;  
};  
  
void push(struct Node** head_ref, int new_data)  
{  
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));  
  
    new_node->data = new_data;  
  
    new_node->next = (*head_ref);  
    new_node->prev = NULL;  
  
    if ((*head_ref) != NULL)  
        (*head_ref)->prev = new_node;  

    (*head_ref) = new_node;  
}  

char pop(struct Node** head_ref)
{
  int data = (*head_ref)->data;
  struct Node* tmp = *head_ref;
  (*head_ref) = tmp->next;
  //  printf("%p\n", tmp->nexat);
  free(tmp);
  (*head_ref)->prev = NULL;  
  return data;
}

int is_empty(struct Node* node)
{
  int i = 0;
    while (node != NULL)
    {              
        node = node->next;
	i++;
    }
    return i;
}

void printList(struct Node* node)  
{  
    struct Node* last;  
    printf("\nTraversal in forward direction \n");  
    while (node != NULL) {  
        printf("%d\n", node->data);  
        last = node;  
        node = node->next;  
    }  
  
    printf("\nTraversal in reverse direction \n");  
    while (last != NULL) {  
        printf("%d\n", last->data);  
        last = last->prev;  
    }  
}  
  
int main()  
{  
    /* Start with the empty list */
    struct Node* head = NULL;  
    push(&head, 7);  
  
    push(&head, 1);  
  
    push(&head, 4);  
   
    printList(head);

    printf("popped: %d\n", pop(&head));

    printList(head);    
  
    //    getchar();  
    return 0;  
} 
