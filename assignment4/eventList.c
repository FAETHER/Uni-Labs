// Example program

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "math.h"
#include <errno.h>
#include <limits.h>

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

typedef struct EVENT_DATE
{
	uint8_t month;
	uint8_t day;
} EVENT_DATE;

typedef struct EVENT
{
	char title[20];
	EVENT_DATE* date;
        struct EVENT* next;
        struct EVENT* prev;
} EVENT;
EVENT* tail = NULL;

typedef struct QEVENT_DATE
{
        char title[20];
	uint8_t month;
	uint8_t day;
} QEVENT_DATE;


// A structure to represent a queue 
struct Queue 
{ 
    int front, rear, size; 
    unsigned capacity; 
    QEVENT_DATE* array; 
}; 
  
// function to create a queue of given capacity.  
// It initializes size of queue as 0 
struct Queue* createQueue(unsigned capacity) 
{ 
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue)); 
    queue->capacity = capacity; 
    queue->front = queue->size = 0;  
    queue->rear = capacity - 1;  // This is important, see the enqueue 
    queue->array = (QEVENT_DATE*) malloc(queue->capacity * sizeof(QEVENT_DATE)); 
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
void enqueue(struct Queue* queue, QEVENT_DATE item) 
{ 
    if (isFull(queue)) 
        return; 
    queue->rear = (queue->rear + 1)%queue->capacity;
    memcpy(&queue->array[queue->rear], &item, sizeof(QEVENT_DATE));
    queue->size = queue->size + 1; 
} 
  
// Function to remove an item from queue.  
// It changes front and size 
QEVENT_DATE dequeue(struct Queue* queue) 
{
    ASSERT(isEmpty(queue) == 0, "Que empty.");
    QEVENT_DATE item = queue->array[queue->front]; 
    queue->front = (queue->front + 1)%queue->capacity; 
    queue->size = queue->size - 1; 
    return item; 
} 
  
// Function to get front of queue
QEVENT_DATE front(struct Queue* queue)
{
    ASSERT(isEmpty(queue) == 0, "Que empty.");
    return queue->array[queue->front];
}
  
// Function to get rear of queue
QEVENT_DATE rear(struct Queue* queue)
{
    ASSERT(isEmpty(queue) == 0, "Que empty.");
    return queue->array[queue->rear];
}

void p_que(struct Queue* que)
{
        QEVENT_DATE item;
	int l = que->size; //is updated, so preserve
	for(int i = 0; i<l; i++)
	  {
	    item = dequeue(que);
	    printf("%s, %d, %d\n", item.title, item.month, item.day);
	  }
	que->size = l;
}

int loc;
long getSizeOfInput(FILE *input)
{
	long retvalue = 0;
	int c;

	if (input != stdin)
	{
		if (-1 == fseek(input, 0L, SEEK_END))
		{
			fprintf(stderr, "Error seek end: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		if (-1 == (retvalue = ftell(input)))
		{
			fprintf(stderr, "ftell failed: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		if (-1 == fseek(input, 0L, SEEK_SET))
		{
			fprintf(stderr, "Error seek start: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* for stdin, we need to read in the entire stream until EOF */
		while (EOF != (c = fgetc(input)))
		{
			if(c == '\n')
			{
				loc++;
			}
			retvalue++;
		}
	}
	fseek(stdin,0,SEEK_SET); //crucial: reset position
	return retvalue;
}

void p_linked(EVENT* head)
{
	head = head->next;
	while (head != NULL)
	  {
	    printf("%s %d, %d\n", head->title, head->date->month, head->date->day);
	    head = head->next;
	  }
}

void merge_lists(EVENT* head, struct Queue* que)
{
	head = head->next;
	QEVENT_DATE item;
	EVENT* ev;
	int c = 0;
	while (head != NULL)
	  {
	    //printf("%s %d, %d\n", head->title, head->date->month, head->date->day);
	    if(c >= 1)
	      {
		item = dequeue(que);
		ev = (EVENT*) calloc(1, sizeof(EVENT));
	        ev->date = (EVENT_DATE*) malloc(sizeof(EVENT_DATE));
		ev->date->day = item.day;
		ev->date->month = item.month;
		memcpy(ev->title, item.title, 20);
		head->prev->next = ev;
		ev->next = head;
		head->prev = ev;		
	      }
	    head = head->next;
	    c++;
	  }
	if(que->size == 1 && tail)
	  {
	    item = dequeue(que);
	    ev = (EVENT*) calloc(1, sizeof(EVENT));
	    ev->date = (EVENT_DATE*) malloc(sizeof(EVENT_DATE));
	    ev->date->day = item.day;
	    ev->date->month = item.month;
	    memcpy(ev->title, item.title, 20);
	    tail->next = ev;
	    ev->prev = tail;
	    ev->next = NULL;
	  }
	return;  
}

void add_events(EVENT* head)
{
	int length = getSizeOfInput(stdin);
	//  printf("loc: %d, len %d\n", loc, length);

	char buffer[length];
	memset(buffer, 0, length);

	size_t rc = fread(buffer, 1, length, stdin);
	ASSERT(rc == (size_t)length, "Read error.");

	char* line = strtok(strdup(buffer), "\n");
	int c = 0;
	EVENT* ev;
	int len;
	char deque = 0;
	EVENT* start = head;

	struct Queue* que = NULL;
	QEVENT_DATE item;
	memset(&item, 0, sizeof(QEVENT_DATE));
	
	while(line)
	{
	        len = fstrlen(line);
		if(len == 1)
		  {
		    //there is no way to tell what we want, a que or linked list from just file
		    //so, assume the first to be linked, then next que
		    if(c > 1)
		      {
			deque = 1;
			ASSERT(que == NULL,"Errr, Can't have more than 2 ques in this implementation! No way to tell what data structure to use!");
			que = createQueue(atoi(line));
			tail = ev;
		      }
		    goto _continue; //skip the first number as it is useless
		  }
		if((c % 2) == 0)
		{
		  if(deque)
		    {		      
		      memcpy(item.title, line, len);
		      deque = 2;
		      c++;
		      goto _continue;
		    }
		  else
		    {
		        ev = (EVENT*) calloc(1, sizeof(EVENT));
			memcpy(ev->title, line, len);
			head->next = ev;
			head->next->prev = head;
			head = ev;			
		    }
		}
		else if(!ev->date && !deque)
		{
			ev->date = (EVENT_DATE*) malloc(sizeof(EVENT_DATE));
			line[2] = 't';
			ev->date->month = atoi(line);
			line[5] = 't';
			ev->date->day = atoi(&line[3]);
		}
		if(deque == 2)
		  {
		    line[2] = 't';
		    item.month = atoi(line);
		    line[5] = 't';
		    item.day = atoi(&line[3]);
		    enqueue(que, item);
		    memset(&item, 0, sizeof(QEVENT_DATE));
		    deque = 1;
		  }
		c++;
		_continue:
		line = strtok(0, "\n");
	}	

	//clean print of the data.
	p_linked(start);
	p_que(que);
	printf("****************************\n");

	merge_lists(start, que);

	printf("Merging the list:\n");
	p_linked(start);

	printf("****************************\n");

	
}

int main()
{
        setbuf(stdout, NULL); //no need for console buffering.

	EVENT head;
	add_events(&head);

	return 0;
}
