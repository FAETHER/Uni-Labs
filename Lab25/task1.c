// C program to implement Bubble Sort on singly linked list 
#include<stdio.h> 
#include<stdlib.h> 
  
/* structure for a node */
struct Node 
{ 
    int data; 
    struct Node *next;
    struct Node *prev;
}; 

struct Node* tail;

/* Function to insert a node at the beginning of a linked list */
void insertAtTheBegin(struct Node **start_ref, int data) 
{
    struct Node *ptr1 = (struct Node*)malloc(sizeof(struct Node));
    static char once = 1;
    if(once)
      {
	tail = ptr1;
	once = 0;
      }
    ptr1->prev = NULL;  
  
    if ((*start_ref) != NULL)  
      (*start_ref)->prev = ptr1;  
  

    ptr1->data = data; 
    ptr1->next = *start_ref; 
    *start_ref = ptr1; 
} 
  
/* Function to print nodes in a given linked list */
void printList(struct Node *start) 
{ 
    struct Node *temp = start; 
    printf("\n"); 
    while (temp!=NULL) 
    { 
        printf("%d ", temp->data); 
        temp = temp->next; 
    } 
} 

/* function to swap data of two nodes a and b*/
void swap(struct Node *a, struct Node *b) 
{ 
    int temp = a->data; 
    a->data = b->data; 
    b->data = temp; 
}

/* Bubble sort the given linked list */
void bubbleSort(struct Node *start) 
{ 
    int swapped, i; 
    struct Node *ptr1; 
    struct Node *lptr = NULL; 
  
    /* Checking for empty list */
    if (start == NULL) 
        return; 
  
    do
    { 
        swapped = 0; 
        ptr1 = start; 
  
        while (ptr1->next != lptr) 
        { 
            if (ptr1->data > ptr1->next->data) 
            {  
                swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } 
    while (swapped); 
} 
  
void delet_last()
{
  struct Node* tmp = tail->prev;
  tail->prev->next = NULL;
  free(tail);
  tail = tmp;
}

void delete(int data, struct Node** head)
{
  struct Node *temp = *head;   
  while (temp!=NULL) 
    { 
      //printf("%d ", temp->data);
      if(temp->data == data)
	{
	  if(temp == tail)
	    {
	      delet_last();
	    }
	  else if(temp == *head)
	    {
	      *head = temp->next;
	      (*head)->prev = NULL;
	      free(temp);
	    }
	  else
	    {
	      temp->prev->next = temp->next;
	      free(temp);
	    }
	}
      temp = temp->next; 
    } 
}

int insert_node(struct Node** head, int new_item, int index)
{
  struct Node* org = *head;
  struct Node* prev;
  int i;
    for(i = 0; *head != NULL && i<index; i++)
      {
	if(i == index-1)
	  {
	    prev = *head;
	  }
	*head = (*head)->next;
      }
    prev->next = (struct Node*) calloc(1, sizeof(struct Node));
    prev->next->data = new_item;
    prev->next->next = *head;

    //    printf("%d %d\n", i, index);
    //ASSERT(i == index, "err, index != i");

    *head = org;
    
    return 1;
}


void add_mid(int a, struct Node **start_ref)
{
  struct Node *temp = *start_ref;
  int i = 0;
  while (temp!=NULL) 
    {
      i++;
      temp = temp->next; 
    }

  i = i/2;
  insert_node(start_ref, a, i);
}

int main() 
{  
    /* start with empty linked list */
    struct Node *start = NULL; 

    char str[100];
    int i = 0;
    while(fgets(str, 100, stdin))
      {	
	insertAtTheBegin(&start, atoi(&str[0]));
	//push(&start, atoi(&str[i]));
	i++;
	if(i>2)
	  {
	    bubbleSort(start);
	    printList(start);
	  }
	if(i == 4)
	  {
	    break;
	  }
      }
    delete(5, &start);
    printList(start);
    
    getchar(); 
    return 0; 
} 
