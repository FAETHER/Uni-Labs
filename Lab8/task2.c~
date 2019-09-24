// Example program

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "math.h"
#include <setjmp.h>

inline size_t fstrlen (const char* s) 
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

typedef struct start_date_t
{
  int day;
  int month;
  int year;
}start_date_t;

struct employees
{
  char name[50];
  int salary;
  start_date_t date;
};

int main()
{
  struct employees a;
  a.date.day = 10;
  a.date.month = 3;
  a.date.year = 2010;
  //printf("%d", sizeof(a.name));
  memset(a.name, 0, sizeof(a.name));
  strncpy(a.name, "John Smith", 10);
  a.salary = 30000;
  
  printf("day: %d\n", a.date.day);
  printf("month: %d\n", a.date.month);
  printf("year: %d\n", a.date.year);
  printf("name: %s\n", a.name);
  printf("salary: %d\n", a.salary);
}
