// Example program

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "math.h"

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

typedef struct EVENT_TIME
{
  uint8_t hour;
  uint8_t min;
}EVENT_TIME;

typedef struct EVENT_DATE
{
  uint8_t month;
  uint8_t day;
  uint16_t year;  
}EVENT_DATE;

typedef struct EVENT
{
  char title[20];
  EVENT_TIME* time;
  EVENT_DATE* date;    
}EVENT;

int delta_x = 0;

EVENT* make_events(char* f, int n)
{
  FILE* file = fopen(f, "rb");
  ASSERT(file, "File does not exist.");

  fseek(file, 0, SEEK_END);
  long length = ftell(file);
  ASSERT(length >= 0, "Empty file");
  fseek(file, 0, SEEK_SET);

  char buffer[length];

  size_t rc = fread(buffer, 1, length, file);
  ASSERT(rc == (size_t)length, "Read error.");
  fclose(file);

  EVENT ts[n];
  memset(ts, 0, sizeof(ts));
  char* line = strtok(strdup(buffer), "\n");
  int c = 0;
  EVENT* ev;
  while(line)
    {
      //printf("%s\n", line);      
      if((c % 3) == 0 || c == 0)
	{
	  //rintf("%d\n", c);
	  ev = &ts[c/3];
	  memcpy(ev->title, line, fstrlen(line));
	}
      else if(ev->time)
	{
	  //printf("ev.time\n");
	  ev->date = (EVENT_DATE*) malloc(sizeof(EVENT_DATE));
	  line[2] = 't';
	  ev->date->month = atoi(line);
	  line[5] = 't';
	  ev->date->day = atoi(&line[3]);
	  ev->date->year = atoi(&line[6]);
	}
      else
	{	  
	  ev->time = (EVENT_TIME*) malloc(sizeof(EVENT_TIME));
	  line[2] = 't';
	  ev->time->hour = atoi(line);
	  ev->time->min = atoi(&line[3]);
	  //printf("In %s\n", line);      
	}
      
      c++;
      line = strtok(0, "\n");
    }

  //printf("Event: %s \n", ts[2].title);
  //printf("Event: %d \n", ts[1].date->year);

  /* printf("Event: %p \n", &ts[0]); */
  /* printf("Event: %p \n", &ts[1]); */

  delta_x = &ts[1] - &ts[0];
  
  EVENT* copy = (EVENT*) malloc(n*sizeof(EVENT));
  memcpy(copy, ts, n*sizeof(EVENT));
  
  return copy;  
}

void print_events(EVENT* p, int index)
{
  //printf("%d\n", sizeof(EVENT));
  p = p+(delta_x*index);
  //printf("Event: %s \n", p->title);	 

  printf("Event: %s at: %d:%d on: %d/%d/%d \n", p->title, p->time->hour, p->time->min,
  	 p->date->month, p->date->day, p->date->year);
}

void print_sel_events(EVENT* ptr, int n,  EVENT_DATE d1, EVENT_DATE d2)
{

  for(int i = 0; i<n; i++)
    {
      EVENT* p = ptr+(delta_x*i);
      /* printf("%d\n", (p->date->day >= d1.day && p->date->day <= d2.day)); */
      /* printf("%d\n", (p->date->month >= d1.month && p->date->month <= d2.month)); */
      /* printf("%d\n", (p->date->year >= d1.year && p->date->year <= d2.year)); */
      
      if((p->date->day >= d1.day && p->date->day <= d2.day) &&
	 (p->date->month >= d1.month && p->date->month <= d2.month) &&
	 (p->date->year >= d1.year && p->date->year <= d2.year)
	 )
	{
	  printf("Event: %s at: %d:%d on: %d/%d/%d \n", p->title, p->time->hour, p->time->min,
		 p->date->day, p->date->month, p->date->year);
	}

    }
    
}
  
int main()
{
  setbuf(stdout, NULL);
  
  char f[50];
  memset(f, 0, sizeof(f));
  printf("Filename:");  
  scanf("%s", &f);

  int n;
  printf("Number:");  
  scanf("%d", &n);
  
  //make_events(f, 2);
  EVENT* ptr = make_events("events.txt", n);
  printf("Schedule of Events:\n");
  for(int i = 0; i<n; i++)
    {
      print_events(ptr, i);
    }

  EVENT_DATE d1;
  EVENT_DATE d2;  
  d1.month = 1;
  d1.day = 1;
  d1.year = 2018;
  d2.month = 12;
  d2.day = 20;
  d2.year = 2019;
  printf("Printing selected events:\n");
  print_sel_events(ptr, n, d1, d2);
  
  return 0;  
}
