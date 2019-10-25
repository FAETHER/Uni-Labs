#include <stdio.h>

int pow(int x, int n);
int invalid_result(int a, int b, int x);
long factorial(long n);

int main(void) {
    int a, b;
    printf("Enter first integer: ");
    scanf("%d", &a);
    printf("Enter second integer: ");
    scanf("%d", &b);
    
    int c = pow(a, b); // step into this
    printf("%d raised to the power of %d is: %d\n", a, b, c);

    int d = invalid_result(1, 2, 3); // step into this
    printf("The result is: %d\n", d);

    long e = factorial(3); // step into this
    printf("3! = %ld\n", e);

    return 0;
}

int pow(int x, int n) {
// This function is intended to return x^n (x to the nth power)
    int i, ans=x;
    if (n == 0)
        return 1;
    else
        for (i = 1; i < n; i++)
            ans = ans* x;
    return ans;
}

int invalid_result(int a, int b, int x) {
    int result = 0;
    switch(x) {
    case 1:
        result = a - b;
	break;
    case 2:
        result = a + b;
	break;
    case 3:
        result = a * b;
	break;
    case 4:
        result = a / b;
	break;
    }
    return result;
}

long factorial(long n) {
    if (n == 0)
        return 1;
    return n * factorial(n-1);
}
