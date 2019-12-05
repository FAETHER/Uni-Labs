// A C Program to demonstrate adjacency list  
// representation of graphs 
#include <stdio.h> 
#include <stdlib.h>
#include<setjmp.h> 
char tree[100]; 
int root(char key) 
{ 
    if(tree[0] != '\0') 
      printf( "Tree already had root\n"); 
    else
        tree[0] = key; 
    return 0; 
} 
  
int set_left(char key, int parent) 
{  
    if(tree[parent] == '\0') 
      printf( "Can't set child at %d,  , no parent found\n", (parent*2)+1); 

    else
        tree[(parent * 2) + 1] = key; 
    return 0; 
} 
  
int set_right(char key, int parent) 
{ 
    if(tree[parent] == '\0') 
      printf( "Can't set child at %d,  , no parent found\n", (parent*2)+2); 
    else
        tree[(parent * 2) + 2] = key; 
    return 0; 
} 
  
int print_tree() 
{ 
  printf( "\n" ); 
    for(int i = 0; i < 100; i++) 
    { 
        if(tree[i] != '\0') 
	  printf( "%c", tree[i] ); 
        else
	  printf( "-" ); 
    } 
    return 0; 
} 

char is_atree(char* arr, int itr)
{
    for(int i = 0; i < itr; i++) 
    { 
      if(tree[0] != '\0')
	{
	  if(tree[(i*2)+1] != '\0' && tree[(i*2)+2] != '\0')
	    {
	      continue;
	    }
	  else
	    {
	      //printf("%c %c\n", tree[(i*2)+1], tree[(i*2)+2]);
	      return 0;
	    }

	}
      else
	{	      
	  printf( "root does not exist!\n" );
	  return 0;
	}
    } 
    return 1; 
}

// Driver Code 
int main() 
{ 
    root('A'); 
    //insert_left('B',0); 
    set_right('C', 0); 
    set_left('D', 0); 
    set_right('E', 1); 
    set_right('F', 2);
    set_right('L', 4);
    //set_right('K', 4);
    print_tree();

    printf("%d\n", is_atree(tree, 2));
    
    return 0; 
} 
