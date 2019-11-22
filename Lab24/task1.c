// C program for array implementation of queue 
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
  
// A structure to represent a queue 
struct Queue 
{ 
    int front, rear, size; 
    unsigned capacity; 
    int* array; 
}; 
  
// function to create a queue of given capacity.  
// It initializes size of queue as 0 
struct Queue* createQueue(unsigned capacity) 
{ 
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue)); 
    queue->capacity = capacity; 
    queue->front = queue->size = 0;  
    queue->rear = capacity - 1;  // This is important, see the enqueue 
    queue->array = (int*) malloc(queue->capacity * sizeof(int)); 
    return queue; 
} 
  
// Queue is full when size becomes equal to the capacity  
int isFull(struct Queue* queue) 
{  return (queue->size == queue->capacity);  } 
  
// Queue is empty when size is 0 
int isEmpty(struct Queue* queue) 
{  return (queue->size == 0); } 
  
// Function to add an item to the queue.   
// It changes rear and size 
void enqueue(struct Queue* queue, int item) 
{ 
    if (isFull(queue)) 
        return; 
    queue->rear = (queue->rear + 1)%queue->capacity; 
    queue->array[queue->rear] = item; 
    queue->size = queue->size + 1; 
    printf("%d enqueued to queue\n", item); 
} 
  
// Function to remove an item from queue.  
// It changes front and size 
int dequeue(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return INT_MIN; 
    int item = queue->array[queue->front]; 
    queue->front = (queue->front + 1)%queue->capacity; 
    queue->size = queue->size - 1; 
    return item; 
} 
  
// Function to get front of queue 
int front(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return INT_MIN; 
    return queue->array[queue->front]; 
} 
  
// Function to get rear of queue 
int rear(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return INT_MIN; 
    return queue->array[queue->rear]; 
} 


// Data structure for stack
struct stack
{
	int maxsize;	// define max capacity of stack
	int top;		
	int *items;
};

// Utility function to initialize stack
struct stack* newStack(int capacity)
{
	struct stack *pt = (struct stack*)malloc(sizeof(struct stack));

	pt->maxsize = capacity;
	pt->top = -1;
	pt->items = (int*)malloc(sizeof(int) * capacity);

	return pt;
}

// Utility function to return the size of the stack
int size(struct stack *pt)
{
	return pt->top + 1;
}

// Utility function to check if the stack is empty or not
int _isEmpty(struct stack *pt)
{
	return pt->top == -1;	// or return size(pt) == 0;
}

// Utility function to check if the stack is full or not
int _isFull(struct stack *pt)
{
	return pt->top == pt->maxsize - 1;	// or return size(pt) == pt->maxsize;
}

// Utility function to add an element x in the stack
void push(struct stack *pt, int x)
{
	// check if stack is already full. Then inserting an element would 
	// lead to stack overflow
	if (_isFull(pt))
	{
		printf("OverFlow\nProgram Terminated\n");
		exit(EXIT_FAILURE);
	}

	printf("Inserting %d\n", x);
	
	// add an element and increments the top index
	pt->items[++pt->top] = x;
}

// Utility function to return top element in a stack
int peek(struct stack *pt)
{
	// check for empty stack
	if (!_isEmpty(pt))
		return pt->items[pt->top];
	else
		exit(EXIT_FAILURE);
}

// Utility function to pop top element from the stack
int pop(struct stack *pt)
{
	// check for stack underflow
	if (_isEmpty(pt))
	{
		printf("UnderFlow\nProgram Terminated\n");
		exit(EXIT_FAILURE);
	}

	printf("Removing %d\n", peek(pt));

	// decrement stack size by 1 and (optionally) return the popped element
	return pt->items[pt->top--];
}


// Driver program to test above functions./ 
int main() 
{ 
    struct Queue* queue = createQueue(1000); 
  
    enqueue(queue, 1); 
    enqueue(queue, 2); 
    enqueue(queue, 3); 
    enqueue(queue, 4);
    enqueue(queue, 5);
    enqueue(queue, 6);
    enqueue(queue, 7);
    enqueue(queue, 8);
    enqueue(queue, 9);
    enqueue(queue, 10); 

    struct stack* st = newStack(1000);

    push(st, dequeue(queue));
    push(st, dequeue(queue));
    push(st, dequeue(queue));
    push(st, dequeue(queue));
    push(st, dequeue(queue));
    push(st, dequeue(queue));
    push(st, dequeue(queue));
    push(st, dequeue(queue));
    push(st, dequeue(queue));
    push(st, dequeue(queue));

    for(int i = 0; i<10; i++)
      {
	printf("%d\n", pop(st));
      }
    /* printf("%d dequeued from queue\n\n", dequeue(queue));  */
    /* printf("%d dequeued from queue\n\n", dequeue(queue));  */
  
  
    /* printf("Front item is %d\n", front(queue));  */
    /* printf("Rear item is %d\n", rear(queue));  */
  
    return 0; 
} 
