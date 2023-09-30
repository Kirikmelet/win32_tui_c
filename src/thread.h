#ifndef PRG_THREAD_H
#define PRG_THREAD_H
#include "Windows.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PRG_MAX_THREADS 32

typedef struct thread_data {
  void *handle;
  unsigned long pid;
} ThreadData;

typedef struct thread_data_pool {
  ThreadData **threads;
  size_t index;
  const size_t max_size;
} ThreadDataPool;

ThreadDataPool *thread_data_pool_init(const size_t max_size);
void thread_data_pool_push_thread(ThreadDataPool *thread_pool,
                                  LPTHREAD_START_ROUTINE proc, void *params);

void thread_data_pool_set_thread(ThreadDataPool *thread_pool, size_t index,
                                 LPTHREAD_START_ROUTINE proc, void *params);

void thread_data_pool_exec(ThreadDataPool *thread_pool);

void thread_data_pool_free(ThreadDataPool *thread_pool);

#endif
