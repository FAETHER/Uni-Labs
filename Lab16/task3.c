#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char* build_string();
void invalid_comparisons();

int main() {

    char *s = build_string(); // step into this
    printf("returned string: %s\n", s);

    invalid_comparisons(); // step into this

    return(0);
}

char* build_string() {
    char* str = (char*) calloc(16, sizeof(char));
    char msg[] = "This should not be printed!";
    
    for (int i = 0; i < 8; i++) {
        str[i] = i + 'a';
    }
    printf("partial string: %s\n", str);
    
    for (int i = 8; i < 16; i++) {
        str[i] = i + 'a';
    }
    
    printf("complete string: %s\n", str);
    return str;
}

void invalid_comparisons() {
    int a = 5;
    if(a==2) {
        printf("something went wrong in integer comparison..\n");
    }
    if(a==5) {
        printf("integer comparison works!\n");
    }
    
    double x = (double) 1 / (double)3;
    double y = (double) 10 / (double)3;
    if (fabs((y - (double)(10 * x))) < 0.01f)
      {
        printf("double comparison works!\n");
      }
    else
      {
	printf("something went wrong in double comparison..\n");
      }
    
    char str[] = "Hello";
    if (strcmp(str,"Hello") == 0) {
        printf("string comparison works!\n");
    } else {
        printf("something went wrong in string comparison..\n");
    }
}

