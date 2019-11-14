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
    
/* Function to insert a node at the beginning of a linked list */
void insertAtTheBegin(struct Node **start_ref, int data) 
{ 
    struct Node *ptr1 = (struct Node*)malloc(sizeof(struct Node)); 
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
  
/* function to swap data of two nodes a and b*/
void swap(struct Node *a, struct Node *b) 
{ 
    int temp = a->data; 
    a->data = b->data; 
    b->data = temp; 
}

void push(Node** head_ref, int new_data)  
{  
    /* 1. allocate node */
    Node* new_node = (Node*) calloc(1, sizeof(Node));  
  
    /* 2. put in the data */
    new_node->data = new_data;  
  
    /* 3. Make next of new node as head and previous as NULL */
    new_node->next = (*head_ref);  
    new_node->prev = NULL;  
  
    /* 4. change prev of head node to new node */
    if ((*head_ref) != NULL)  
        (*head_ref)->prev = new_node;  
  
    /* 5. move the head to point to the new node */
    (*head_ref) = new_node;  
}

void pop(Node** head_ref, int new_data)  
{  
    
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

    
    getchar(); 
    return 0; 
} 
