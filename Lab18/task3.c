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

typedef struct complex_t
{
    float real;
    float imag;
} complex_t;

complex_t add(complex_t n1, complex_t n2)
{
      complex_t temp;
      temp.real = n1.real + n2.real;
      temp.imag = n1.imag + n2.imag;
      return(temp);
}

complex_t sub(complex_t n1, complex_t n2)
{
      complex_t temp;
      temp.real = n1.real - n2.real;
      temp.imag = n1.imag - n2.imag;
      return(temp);
}

int main()
{
    complex_t n1, n2, temp;
    printf("For 1st complex number \n");
    printf("Enter real and imaginary part respectively:\n");
    scanf("%f %f", &n1.real, &n1.imag);
    printf("\nFor 2nd complex number \n");
    printf("Enter real and imaginary part respectively:\n");
    scanf("%f %f", &n2.real, &n2.imag);
    temp = add(n1, n2);
    printf("Sum = %.1f + %.1fi\n", temp.real, temp.imag);
    temp = sub(n1, n2);
    printf("Sub = %.1f - %.1fi\n", temp.real, temp.imag);
    return 0;
}
