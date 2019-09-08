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

typedef struct Exam //not really need to be typedef, but by convention i shall make it.
{
  char* answers;
  uint16_t num; 
  uint16_t line;
  char ids[50]; //just assume to be 50 max, because I am lazy to deal with memory for this.
  char ans[4500];
  float perc[50];
  uint16_t* missed;
}Exam;

Exam global;

void scan_exam_data() //this call is pointless, but I am following the directions.
{
  char str[100]; // todo: normally we would want to know the dynamic context.
  memset(str, 0, sizeof(str)); //no need for garbage memory.
  global.line = 0; //count lines in file
  int len;
  int i;
  int id_index = 0;

  memset(global.ids, ' ', sizeof(global.ids));

  while(fgets(str, 100, stdin))
    {
      puts(str);
      len = fstrlen(str);
      
      if(!global.line) //shortcut for exceptional 1st line
	{	  
	  global.answers = (char*) malloc(len+1); //in production applications, one should avoid using malloc very often.
	  ASSERT(global.answers, "Out of system memory!");
	  for(i = 0; i<len && str[i] != ' '; i++) //until we reach space separator. Assumed to exist.
	    {
	      //*((char*)&global.num) = str[i+1];
	      *((char*)&global.num) = str[i] - '0'; //convert ascii to num
	      //assume that the count is the 1st char + next. This will limit us to max of 0x0000FFFF.
	    }
	  memcpy(global.answers, str+i+1, len-i);
	}
      else 
	{
	  for(i = 0; i<len; i++) //until we reach space separator. Assumed to exist.
	    {
	      *((char*)&global.ids[id_index + i]) = str[i]; //just copy ids only. tokenize a bit
	      if(str[i] == ' ')
		{
		  memcpy(&global.ans[(global.line-1) * global.num], &str[i+1], len-i-1);
		  break;
		}
	    }
	  id_index += i+1;
	}

      global.line++;
      ASSERT(global.line < 50, "This program is capped at 50 questions");
    }

    global.ids[id_index] = '\0';

}



void analyze_data()
{
  int cerr = 0;
  int i;
  int z;

  global.missed = (uint16_t*) malloc(global.num); //kyryl: shit-code incomming :>)
  ASSERT(global.missed, "Out of system memory!");

  
  for(z = 0; z<global.line-1; z++)
    {      
      for(i = 0; i<global.num; i++)
	{
	  //printf(" %c ", global.ans[i]);
	  //printf(" %c ", global.answers[i]);
	  if(global.answers[i] != global.ans[i+(z*global.num)])
	    {
	      cerr++;
	      global.missed[i]++;
	    }
	}
      // printf(" %d ", cerr);
      global.perc[z] = ((float)(global.num - cerr) / global.num) * 100;
      //printf(" %f ", global.perc[z]);
      cerr = 0;
    }
}

void print_data()
{
  puts("Exam Report\n");
  int i;
  printf("Question");
  for(i = 1; i<=global.num; i++)
    {
      printf(" %d ", i);
    }
  printf("\n");
  printf("Answer  ");
  for(i = 0; i<global.num; i++)
    {
      printf(" %c ", global.answers[i]);
    }
  printf("\nID       Score(%) \n");
  int len=0;
  int test = 0;
  for(i = 0; i<global.line-1; i++)
    {
      //       printf("%d      ", sstrlen(&global.ids[4]));
      len += sstrlen(&global.ids[len]); //with this, id can be any length actually
      len++;
      //  if(!i) //lazy hack as the math does not work out.
      //	printf("%.*s      %f\n", len/(i+1), &global.ids[0], global.perc[0]);
      
      printf("%.*s      %f\n", len/(i+1), &global.ids[test], global.perc[i]);
      test += len/(i+1); //retarded code, but it works.
    }
  printf("Question");
  for(i = 1; i<=global.num; i++)
    {
      printf(" %d ", i);
    }
  printf("\nMissed by");
  for(i = 0; i<global.num; i++)
    {
      printf(" %d ", global.missed[i]);
    }
  
}

int main()
{

  scan_exam_data();
  printf("num: %d\n", global.num);
  printf("answers: %s\n", global.answers);
  printf("%s\n", global.ids);
  printf("%s\n", global.ans);

  analyze_data();

  print_data();
	
  
  return 0;  
}
