#include <stdio.h>

long factorial(long n);

int main(void) {
    
    int i = 10; 
	while (i--) {
		long f = factorial(i); 
		printf("%d! = %ld\n", i, f);
	}
	
    return 0;
}

long factorial(long n) {
    if (n == 0)
        return 1;
    return n * factorial(n-1);
}

