// Example program

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "math.h"
#include <errno.h>

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
} EVENT_TIME;

typedef struct EVENT_DATE
{
	uint8_t month;
	uint8_t day;
	uint16_t year;
} EVENT_DATE;

typedef struct EVENT
{
	char title[20];
	EVENT_TIME* time;
	EVENT_DATE* date;
	struct EVENT* next;
} EVENT;

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

void add_events(EVENT* head)
{
	int length = getSizeOfInput(stdin);
	//  printf("loc: %d, len %d\n", loc, length);

	char buffer[length];
	memset(buffer, 0, length);

	size_t rc = fread(buffer, 1, length, stdin);
	ASSERT(rc == (size_t)length, "Read error.");

	int n = (loc+1)/3;
	EVENT* ts[n];
	char* line = strtok(strdup(buffer), "\n");
	int c = 0;
	EVENT* ev;
	while(line)
	{
		if((c % 3) == 0 || c == 0)
		{
		        ev = (EVENT*) calloc(n, sizeof(EVENT));
			ts[c/3] = ev;
			memcpy(ev->title, line, fstrlen(line));
			if((c/3) == (n-1))
			{
				ev->next = NULL; //kill the list
			}
			else if(c != 0)
			{
			  ts[(c/3)-1]->next = ev;
			  //ev->next = &ts[(c/3)+1];
			}
		}
		else if(ev->time)
		{
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
		}

		c++;
		line = strtok(0, "\n");
	}	

	//well, ugh, since the list is linked randomly, it is
	//easier to hack together a new one and reasign it.
	EVENT* index[n];
	memset(index, 0, sizeof(int)*n);
	int self = 0;

	//optimistic attempt, think about this:
	//how do we sort without modifying the memory?
	//is this possible at all ? How does this linked list complicate it?

	/* for(c=0; c<n; c++) */
	/*   { */
	/*     char min = ts[self].title[0]; */
	/*   d_check:; */
	/*     for(int z = 0; z<n; z++) */
	/* 	{ */
	/* 	  if(index[z]->title[0] == min) */
	/* 	    { */
	/* 	      if(self == n-1) */
	/* 		{ */
	/* 		  goto next; */
	/* 		} */
	/* 	      min = ts[++self].title[0]; */
	/* 	      goto d_check; */
	/* 	    } */
	/* 	} */
	/*     printf("min %c, %d\n",min, c); */
	/*     for(int i = 0; i<n; i++) */
	/* 	{ */
	/* 	  for(int z = 0; z<n; z++) */
	/* 	    { */
	/* 	      if(index[z] == &ts[i]) */
	/* 		{ */
	/* 		  goto skip; */
	/* 		} */
	/* 	    } */
	/* 	  if(ts[i].title[0] < min) */
	/* 	    { */
	/* 	      min = ts[i].title[0]; */
	/* 	      index[c] = &ts[i]; */
	/* 	    } */
	/* 	skip:; */
	/* 	} */
	/*     if(index[c] == NULL) */
	/* 	{ */
	/* 	  index[c] = &ts[c]; */
	/* 	}   */
	/*   } */

	//   next:;


	//sort alpabetically and wire up the list.

	char min = ts[0]->title[0];
	for(int i = 1; i<n; i++)
	{
		if(ts[i]->title[0] < min)
		{
			min = ts[i]->title[0];
			index[0] = ts[i];
		}
	}

	int a[n];
	memset(a, 0x6666, sizeof(int)*n);
	for(int i = 0; i<n; i++)
	{
		if(ts[i]->title[0] == index[0]->title[0])
		{
			continue;
		}
		a[i] = ts[i]->title[0] - index[0]->title[0];
	}

	/* for(int h = 0; h<n; h++) */
	/*   { */
	/*     printf("itr %d\n", a[h]); */
	/*   } */

	for(int z = 1; z<n; z++)
	{
		int min = a[0];
		int idt = 0;
		for(int i = 1; i<n; i++)
		{
			if((a[i] < min))
			{
				min = a[i];
				idt = i;
			}
		}
		//	      printf("idt %d, min %d\n", idt, min);
		a[idt] = 0x6666;
		index[z] = ts[idt];
	}

	c = 0;
	for(head->next = index[0]; head != NULL && c<n; c++)
	{
		head->next = index[c];
		head = head->next;
	}
	head->next = NULL;
	return;


	/* printf("%s\n", index[0]->title); */
	/* printf("%s\n", index[1]->title); */
	/* printf("%s\n", index[2]->title); */
	/* printf("%s\n", index[3]->title); */
	//      printf("%s\n", index[4]->title);
	/* for(head = head->next; head != NULL;) */
	/*   { */
	/*     for(int i = 0; i<n; i++) */
	/* 	{ */

	/* 	} */
	/*     head = head->next; */
	/*   } */

	/* for (int i = 0; i < n; i++)                     //Loop for ascending ordering */
	/*   { */
	/*     for (int j = 0; j < n; j++)             //Loop for comparing other values */
	/* 	{ */
	/* 	  if (ts[j].title[0] > ts[i].title[0])                //Comparing other array elements */
	/* 	    { */
	/* 	      char t =  ts[i].title[0]; */
	/* 	      ts[i].title[0] =  ts[j].title[0]; */
	/* 	      ts[j].title[0] = t; */
	/* 	      EVENT* tmp = ts[i].next;         //Using temporary variable for storing last value */
	/* 	      ts[i].next = ts[j].next;            //replacing value */
	/* 	      ts[j].next = tmp;             //storing last value */
	/* 	    } */
	/* 	} */
	/*   } */

	/* for (head = &ts[0]; head != NULL;)                     //Loop for ascending ordering */
	/*   {         */
	/*     //printf("Event: %s at: %d:%d on: %d/%d/%d \n", head->title, head->time->hour, head->time->min, */
	/*     //	head->date->month, head->date->day, head->date->year);      */
	/*     head = head->next; */
	/*   } */
	/*   return;   */

	/* head->next = &ts[0]; */


}

void print_list(EVENT* head)
{
	printf("Schedule of Events:\n");
	head = head->next;
	for(; head != NULL;)
	{
	  printf("    Event: %s at: ", head->title);
	  /* %d:%d on: %d/%d/%d  */
	  if(head->time->hour < 10)
	    {
	      printf("0%d:", head->time->hour);
	    }
	  else
	    {
	       printf("%d:", head->time->hour);
	    }
	  if(head->time->min < 10)
	    {
	      printf("0%d on:", head->time->min);
	    }
	  else
	    {
	       printf("%d on:", head->time->min);
	    }
	  if(head->date->month < 10)
	    {
	      printf("0%d/", head->date->month);
	    }
	  else
	    {
	       printf("%d/", head->date->month);
	    }
	  if(head->date->day < 10)
	    {
	      printf("0%d/", head->date->day);
	    }
	  else
	    {
	       printf("%d/", head->date->day);
	    }
	  if(head->date->year < 10)
	    {
	      printf("0%d\n", head->date->year);
	    }
	  else
	    {
	       printf("%d\n", head->date->year);
	    }
	  head = head->next;
	}

}

void print_sel_events(EVENT* head, EVENT_DATE d1)
{
	printf("Date %d/%d/%d\n", d1.month, d1.day, d1.year);
	printf("Events:\n");

	head = head->next;
	for(; head != NULL;)
	{
		if((head->date->month == d1.month) && (head->date->day == d1.day) &&
		        (head->date->year == d1.year))
		{
		  printf("    Event: %s at: ", head->title);
		  if(head->time->hour < 10)
		    {
		      printf("0%d:", head->time->hour);
		    }
		  else
		    {
		      printf("%d:", head->time->hour);
		    }
		  if(head->time->min < 10)
		    {
		      printf("0%d\n", head->time->min);
		    }
		  else
		    {
		      printf("%d\n", head->time->min);
		    }
		}
		head = head->next;
	}
}

int main()
{
	setbuf(stdout, NULL);

	EVENT head;

	add_events(&head);

	print_list(&head);

	EVENT_DATE d1;
	d1.month = 6;
	d1.day = 15;
	d1.year = 2018;
	print_sel_events(&head, d1);

	return 0;
}
