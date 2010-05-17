#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "task.h"

typedef char Block[1024];

Block *a[1024];

void* clear_task(Task t) {
  Block *b = malloc(sizeof(Block));
  a[(int)t->arg] = b;
  sleep(rand() % 5);
  return NULL;
}

int main() {
  sranddev();
  Task tasks[1024];
  int i;
  for (i=0; i < 1024; i++)
    task_new(&tasks[i], &clear_task, (void*)i);
  pthread_exit(NULL);
  return 0;
}
