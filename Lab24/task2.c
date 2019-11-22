#include <stdio.h>
#include <stdlib.h>

struct node {
  int data;
  struct node *prev, *next;
};

struct node *head = NULL, *tail = NULL;

struct node * createNode(int data) {
  struct node *newnode = (struct node *)malloc(sizeof (struct node));
  newnode->data = data;
  newnode->next = newnode->prev = NULL;
  return (newnode);
}

/*
 * create sentinel(dummy head & tail) that
 * helps us to do insertion and deletion 
 * operation at front and rear so easily.  And
 * these dummy head and tail wont get deleted
 * till the end of execution of this program
 */

void createSentinels() {
  head = createNode(0);
  tail = createNode(0);
  head->next = tail;
  tail->prev = head;
}

/* insertion at the front of the queue */
void enqueueAtFront(int data) {
  struct node *newnode, *temp;
  newnode = createNode(data);
  temp = head->next;
  head->next = newnode;
  newnode->prev = head;
  newnode->next = temp;
  temp->prev = newnode;
}

/*insertion at the rear of the queue */
void enqueueAtRear(int data) {
  struct node *newnode, *temp;
  newnode = createNode(data);
  temp = tail->prev;
  tail->prev = newnode;
  newnode->next = tail;
  newnode->prev = temp;
  temp->next = newnode;
}

/* deletion at the front of the queue */
void dequeueAtFront() {
  struct node *temp;
  if (head->next == tail) {
    printf("Queue is empty\n");
  } else {
    temp = head->next;
    head->next = temp->next;
    temp->next->prev = head;
    free(temp);
  }
  return;
}


/* deletion at the rear of the queue */

void dequeueAtRear()  {
  struct node *temp;
  if (tail->prev == head) {
    printf("Queue is empty\n");
  } else {
    temp = tail->prev;
    tail->prev = temp->prev;
    temp->prev->next = tail;
    free(temp);
  }
  return;
}

/* display elements present in the queue */
void display() {
  struct node *temp;

  if (head->next == tail) {
    printf("Queue is empty\n");
    return;
  }

  temp = head->next;
  while (temp != tail) {
    printf("%-3d", temp->data);
    temp = temp->next;
  }
  printf("\n");
}

int main()
{
  int data, ch;
  createSentinels();
  enqueueAtFront(10);

  display();
  
  return 0;
}
