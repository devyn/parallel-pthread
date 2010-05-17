#include <stdlib.h>
#include <pthread.h>
#include "task.h"

void* task_runner(void* t_v) {
  Task t = t_v;
  t->value = (*t->fun)(t);
  t->running = 0;
  pthread_exit(t->value);
}

int task_new(Task *t, void *(*fun)(Task), void *arg) {
  *t = malloc(sizeof(struct Task));
  (*t)->running = 1;
  (*t)->arg = arg;
  (*t)->fun = fun;
  if (pthread_create(&(*t)->thread, NULL, *task_runner, (void*)*t) != 0)
    return 2;
  return 0;
}

void* task_get(Task t) {
  if (t->running) {
    void* n;
    pthread_join(t->thread, &n);
    return n;
  } else {
    return t->value;
  }
}

void task_destroy(Task t) {
  pthread_kill(t->thread, 1);
  free(t);
}
