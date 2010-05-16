#ifndef TASK_H
#define TASK_H

#include <pthread.h>

struct Task {
  pthread_t thread;
  void*     value;
  int       running;
  void *(*fun)(struct Task*);
};

typedef struct Task* Task;

void* task_runner(void* t);
int   task_new(Task* t, void *(*fun)(Task));
void* task_get(Task t);
void  task_destroy(Task t);

#endif
