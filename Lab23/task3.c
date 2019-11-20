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
int isEmpty(struct stack *pt)
{
	return pt->top == -1;	// or return size(pt) == 0;
}

// Utility function to check if the stack is full or not
int isFull(struct stack *pt)
{
	return pt->top == pt->maxsize - 1;	// or return size(pt) == pt->maxsize;
}

// Utility function to add an element x in the stack
void push(struct stack *pt, int x)
{
	// check if stack is already full. Then inserting an element would 
	// lead to stack overflow
	if (isFull(pt))
	{
		printf("OverFlow\nProgram Terminated\n");
		exit(EXIT_FAILURE);
	}

	//printf("Inserting %d\n", x);
	
	// add an element and increments the top index
	pt->items[++pt->top] = x;
}

// Utility function to return top element in a stack
int peek(struct stack *pt)
{
	// check for empty stack
	if (!isEmpty(pt))
		return pt->items[pt->top];
	else
		exit(EXIT_FAILURE);
}

// Utility function to pop top element from the stack
int pop(struct stack *pt)
{
	// check for stack underflow
	if (isEmpty(pt))
	{
	        return -1;
	}

	//printf("Removing %d\n", peek(pt));

	// decrement stack size by 1 and (optionally) return the popped element
	return pt->items[pt->top--];
}

char* postfix(char* s)
{
  int len = fstrlen(s);
  int idx = 0;
  char wait = 0;
  struct stack* pt = newStack(len);
  char* str = (char*) malloc(len*2);
  memset(str, ' ', len*2);
    for(int i = 0; i<len; i++)
      {
	if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
	  {
	  catchup:;
	    char a = (char)pop(pt);
	    char b = (char)pop(pt);
	    if(a == -1 && b == -1)
	      {
		//printf("%d\n", idx);	        
		str[(idx-4)/2] = s[i];
		continue;
	      }
	    else if (b == -1 && a)
	      {
		//not second operand not yet reached.
		push(pt, (int)a);
		wait = s[i];
		continue;
	      }
	    if(wait)
	      {
		str[idx] = b;
		str[idx+1] = wait;
		str[idx+2] = a;
		idx+=6;
		wait = 0;
		goto catchup;
	      }
	    str[idx] = b;
	    str[idx+1] = s[i];
	    str[idx+2] = a;
	    idx+=6;
	  }
	else if(s[i] != ' ')
	  {
	    push(pt, (int)s[i]);
	  }
      }
    return str;
}

int main()
{
  printf("%s\n", postfix("1 2 +"));
  printf("%s\n", postfix("1 2 3 * + 4 +"));
  printf("%s\n", postfix("1 2 + 3 4 + *"));
  printf("%s\n", postfix("1 2 + 3 + 4 +"));
}
