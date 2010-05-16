#include "task.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void* task_a(Task t) {
  unsigned long *a = malloc(sizeof(int));
  *a = (unsigned long)rand() % (unsigned long)pow(2, 32);
  return (void*) a;
}

void* task_b(Task t) {
  unsigned long *b = malloc(sizeof(int));
  *b = (unsigned long)rand() % (unsigned long)pow(2, 32);
  return (void*) b;
}

void* task_c(Task t) {
  Task a, b;
  task_new(&a, &task_a);
  task_new(&b, &task_b);
  unsigned long *av = task_get(a);
  unsigned long *bv = task_get(b);
  unsigned long *c = malloc(sizeof(int));
  *c = *av * *bv;
  return (void*) c;
}

int main() {
  sranddev();
  Task c1, c2, c3;
  task_new(&c1, &task_c);
  task_new(&c2, &task_c);
  task_new(&c3, &task_c);
  unsigned long *vc1 = task_get(c1);
  unsigned long *vc2 = task_get(c2);
  unsigned long *vc3 = task_get(c3);
  printf("%lu\n", *vc1 - *vc2 - *vc3);
  return 0;
}
