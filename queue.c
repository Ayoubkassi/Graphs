#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define QUEUE_EMPTY CHAR_MIN



typedef struct node{
  char *value;
  struct node *next;
} node;

typedef struct{
  node *head;
  node *tail;
} queue;

void init_queue(queue *q){
  q->head = NULL;
  q->tail = NULL;
}


bool enqueue(queue *q, char *value){
  node *newnode = malloc(sizeof(node));
  if(newnode == NULL) return false;
  newnode->value = value;
  newnode->next = NULL;
  if(q->tail != NULL){
    q->tail->next = newnode;
  }
  q->tail = newnode;
  if(q->head == NULL){
    q->head = newnode;
  }
  return true;
}

// bool empty(queue* q){
//   return (q->head == NULL && q->tail == NULL);
// }

char* dequeue(queue *q){
  if(q->head == NULL) return QUEUE_EMPTY;
  node *tmp = q->head;
  char* result = tmp->value;
  q->head = q->head->next;
  if(q->head == NULL){
    q->tail = NULL;
  }
  return result;
}


int main(){
  queue q1;
  init_queue(&q1);
  enqueue(&q1, "S1");
  enqueue(&q1, "S2");
  enqueue(&q1, "S3");
  enqueue(&q1, "S4");
  char *t;
  while((t = dequeue(&q1)) != QUEUE_EMPTY){
    printf("%s \n",t);
  }
}
