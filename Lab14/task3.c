// Example program

#include "header.h"

size_t fstrlen (const char* s) 
{
	register const char* i;
	for(i=s; *i; ++i);
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


void sto_lower(char* in)
{
  while(*in)
    {
      *in = tolower(*in);
      in++;
    }
  *(in-1) = '\0';
}

typedef struct {int day;int month;int year;}date_t;
typedef struct {date_t* strat_date;date_t* end_date;}interval_t;


void tell(interval_t* intr)
{
  int x = (intr->end_date->year*12) + intr->end_date->month;
  if(intr->end_date->day > 30)
    {
      x++;
    }
  int y = (intr->strat_date->year*12) + intr->strat_date->month;
  if(intr->strat_date->day > 30)
    {
      y++;
    }

  printf("Number of months: %d\n", abs(y-x));  
}

int main() 
{

  char a[] = "10/16/2017\n";
  char b[] = "10/16/2018\n";

  date_t* ptr = (date_t*) calloc(2, sizeof(date_t));
  interval_t* intr = (interval_t*) calloc(1, sizeof(interval_t));

  intr->strat_date = ptr;

  ptr->month =  atoi(a);
  ptr->day = atoi(&a[3]);
  ptr->year = atoi(&a[6]);
  
  ptr += sizeof(date_t);
  // or write ptr++ but I do not trust that. Makes the code unclear.
  
  ptr->month =  atoi(b);
  ptr->day = atoi(&b[3]);
  ptr->year = atoi(&b[6]);
  

  intr->end_date = ptr;

  tell(intr);
  
  return 0; 
} 
