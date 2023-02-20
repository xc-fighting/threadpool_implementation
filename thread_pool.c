#include "thread_pool.h"

void* thread_function(void* args) {

  thread_pool_t* pool = (thread_pool_t*)args;
  task_t entry;
  for(;;) {
  	pthread_mutex_lock(&pool->thread_pool_mutex);
    // if cur task queue is empty, wait in cond
    while(pool->cur_task_size == 0 
          && pool->shutdown == false) {
      // it will auto unlock mutex, when function return, it lock the mutex
      pthread_cond_wait(&pool->empty_task_cond, &pool->thread_pool_mutex);
    }
    if(pool->shutdown == true) {
       printf("shutdown the pool\n");
       pthread_mutex_unlock(&pool->thread_pool_mutex);
       break;
    }
    //when it get here, it already lock the mutex
    int idx = pool->front;
    entry.task_func = pool->task_queue[idx].task_func;
    entry.args = pool->task_queue[idx].args;
    pool->front = (pool->front + 1) % pool->total_task_size;
    pool->cur_task_size--;
    // signal the full_thread_cond
    pthread_cond_signal(&pool->full_thread_cond);
  	pthread_mutex_unlock(&pool->thread_pool_mutex);
    // run the function here
  	entry.task_func(entry.args);
  }
  return NULL;
}

thread_pool_t* init_thread_pool(int pool_size,
                              int task_size) {
  thread_pool_t* pool = (thread_pool_t*)malloc(sizeof(thread_pool_t));
  if(pool == NULL) {
     return NULL;
  }
  // set the front and rear
  // total pool size and task size
  pool->front = 0;
  pool->rear = 0;
  pool->total_pool_size = pool_size;
  pool->total_task_size = task_size;
  // assign thread queue
  pool->thread_queue = (pthread_t*)malloc(sizeof(pthread_t) * pool->total_pool_size);
  if(pool->thread_queue == NULL) {
    free(pool);
    return NULL;
  }

  // assign the task queue
  pool->task_queue = (task_t*)malloc(sizeof(task_t) * pool->total_task_size);
  if(pool->task_queue == NULL) {
    free(pool->thread_queue);
    free(pool);
    return NULL;
  }
  pthread_mutex_init(&pool->thread_pool_mutex, NULL);
  pthread_cond_init(&pool->empty_task_cond, NULL);
  pthread_cond_init(&pool->full_thread_cond, NULL);
  pool->shutdown = false;
  // start all of the thread here
  for(int idx = 0; idx < pool_size; idx++) {
    int ret = pthread_create(&pool->thread_queue[idx], NULL, thread_function, pool);
    if(ret < 0) {
       return NULL;
    }
    pthread_detach(pool->thread_queue[idx]);
  }

  return pool;
  
}

void add_task_to_thread_pool(thread_pool_t* pool,
                             task_t* task_item) {
  pthread_mutex_lock(&pool->thread_pool_mutex);
  printf("add task to task queue\n");
  while(pool->cur_task_size == pool->total_task_size 
        && pool->shutdown == false) {
    //wait in the full cond
    pthread_cond_wait(&pool->full_thread_cond, &pool->thread_pool_mutex);
  }
  if(pool->shutdown == true) {
    pthread_mutex_unlock(&pool->thread_pool_mutex);
    return;
  }
  // add the task here, when it get here, mutex is locked
  pool->task_queue[pool->rear] = *task_item;
  pool->rear = (pool->rear + 1) % pool->total_task_size;
  pool->cur_task_size++;
  pthread_cond_signal(&pool->empty_task_cond);
  pthread_mutex_unlock(&pool->thread_pool_mutex);
  return;
}


void destroy_thread_pool(thread_pool_t* pool) {
  printf("destroy the thread pool\n");
  if(pool == NULL) {
     return;
  }

  for(int idx = 0; idx < pool->total_pool_size; idx++) {
    pthread_cancel(pool->thread_queue[idx]);
    pthread_cond_signal(&pool->empty_task_cond);
  }

  if(pool->task_queue != NULL) {
     free(pool->task_queue);
  }

  if(pool->thread_queue != NULL) {
     free(pool->thread_queue);
  }

  pthread_mutex_destroy(&pool->thread_pool_mutex);
  pthread_cond_destroy(&pool->full_thread_cond);
  pthread_cond_destroy(&pool->empty_task_cond);

  free(pool);
  pool = NULL;
  return;

}