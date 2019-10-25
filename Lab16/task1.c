#include <stdio.h>

int sum_of_2_integers(int a, int b);
void swap_2_integers(int* a, int* b);
int sum_of_odds();

int main(void) {
    int x, y;
    printf("Enter first integer (x): ");
    scanf("%d", &x);
    printf("Enter second integer (y): ");
    scanf("%d", &y);
    
    int z = sum_of_2_integers(x, y); // step over this
    printf("%d + %d = %d\n", x, y, z);

    swap_2_integers(&x, &y); // step into this
    printf("after swapping, x = %d and y = %d\n", x, y);

    int w = sum_of_odds(); // step into this
    printf("The sum of odd integers between 1 and 100 is: %d\n", w);

    return 0;
}

int sum_of_2_integers(int a, int b) {
    return a + b;
}

void swap_2_integers(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int sum_of_odds() {
// This function is intended to return the sum of all odd 
// integers between 1 to 100 inclusive (1, 3, 5, ..., 99)
    int i, sum = 0;

    for(i = 1; i <= 100; i += 2) {
        sum += i; // watch sum
        // you can also set a conditional breakpoint here as
        // close as possible to the last iteration of the loop
    }
    return sum;
}
