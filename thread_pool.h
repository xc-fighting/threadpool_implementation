#ifndef _THREAD_POOL_
#define _THREAD_POOL_

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct task {
	void* args;
	void (*task_func)(void*);
} task_t;


typedef struct thread_pool {
  // the current number of tasks should be 
  // less than or equal to total_task_size
  int cur_task_size;
  // total number of threads in pool
  int total_pool_size;
  // total number of tasks
  int total_task_size;
  // front of task queue
  int front;
  // rear of task queue
  int rear;
  // the queue to add tasks
  struct task* task_queue;
  // thread queue
  pthread_t* thread_queue;
  // this is a mutex to protect add_task and thread function
  pthread_mutex_t thread_pool_mutex;
  // condition variable when no task
  pthread_cond_t empty_task_cond;
  // condition variable when all thread is busy
  pthread_cond_t full_thread_cond;

  bool shutdown;
} thread_pool_t;

void* thread_function(void* args);
extern thread_pool_t* init_thread_pool(int pool_size, int task_size);
extern void add_task_to_thread_pool(thread_pool_t* pool, task_t* task_item);
extern void destroy_thread_pool(thread_pool_t* pool);


#endif