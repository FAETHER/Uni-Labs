
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "math.h"
#include <setjmp.h>
#include "time.h"


int max(int a[], int n) {
  int c, max, index;
 
  max = a[0];
  index = 0;
 
  for (c = 1; c < n; c++) {
    if (a[c] > max) {
      index = c;
      max = a[c];
    }
  }
 
  return max;
}

int min(int a[], int n) {
  int c, max, index;
 
  max = a[0];
  index = 0;
 
  for (c = 1; c < n; c++) {
    if (a[c] < max) {
      index = c;
      max = a[c];
    }
  }
 
  return max;
}

int* Double(int* arr, int size)
{
  int* arrr = (int*) malloc(sizeof(int)*size);
  
  for(int i = 0; i<size; i++)
    {
      arrr[i] = ldexp(1, arr[i]);
    }
  return arrr;
}

void swap(int *xp, int *yp)  
{  
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}  
  
void selectionSort(int arr[], int n)  
{  
    int i, j, min_idx;  
  
    // One by one move boundary of unsorted subarray  
    for (i = 0; i < n-1; i++)  
    {  
        // Find the minimum element in unsorted array  
        min_idx = i;  
        for (j = i+1; j < n; j++)  
        if (arr[j] < arr[min_idx])  
            min_idx = j;  
  
        // Swap the found minimum element with the first element  
        swap(&arr[min_idx], &arr[i]);  
    }  
}  

int* task3(int* arr, int size)
{
  int* arrr = (int*) malloc(sizeof(int)*size);
  memcpy(arrr, arr, sizeof(int)*size);

  selectionSort(arrr, size);
  
  return arrr;
}
