#include "thread.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ThreadDataPool *thread_data_pool_init(const size_t max_size) {
  if (max_size <= 0) {
    errprint("max_size must always >0!\n");
    return NULL;
  }
  ThreadDataPool basic_empty_pool = {
      .max_size = max_size, .threads = NULL, .index = 0};
  ThreadDataPool *thread_pool = malloc(sizeof *thread_pool);
  if (thread_pool == NULL) {
    errprint("Failed to malloc memory!");
    return thread_pool;
  }
  /* I fucking hate this */
  memcpy(thread_pool, &basic_empty_pool, sizeof *thread_pool);
  thread_pool->threads =
      calloc(thread_pool->max_size, sizeof(PHANDLE) + sizeof(unsigned long));
  for (size_t i = 0; i < max_size; ++i) {
    thread_pool->threads[i] = malloc(sizeof(PHANDLE) + sizeof(unsigned long));
    if (thread_pool->threads[i] == NULL) {
      errprint("Did not properly allocate for thread!");
      exit(-1);
    }
    ThreadData *thread = thread_pool->threads[i];
    thread->pid = -1;
    thread->handle = NULL;
  }
  return thread_pool;
}

void thread_data_pool_push_thread(ThreadDataPool *thread_pool,
                                  LPTHREAD_START_ROUTINE proc, void *params) {
  size_t *index = &thread_pool->index;
  if (*index >= thread_pool->max_size) {
    errprint("Index is over max size!");
    return;
  }
  thread_data_pool_set_thread(thread_pool, *index, proc, params);
  (*index)++;
}

void thread_data_pool_set_thread(ThreadDataPool *thread_pool, size_t index,
                                 LPTHREAD_START_ROUTINE proc, void *params) {
  thread_pool->threads[index]->handle =
      CreateThread(NULL, 0, proc, params, CREATE_SUSPENDED,
                   &thread_pool->threads[index]->pid);
}

void thread_data_pool_exec(ThreadDataPool *thread_pool) {
  void *handles[] = {NULL};
  unsigned long handle_count = 0;
  for (size_t i = 0; i < thread_pool->max_size; ++i) {
    ThreadData *thread_data = thread_pool->threads[i];
    if (thread_data->pid > 0 && thread_data->handle != NULL) {
      handles[i] = thread_data->handle;
      handle_count++;
      ResumeThread(handles[i]);
    }
  }
  if (handle_count <= 0) {
    return;
  }
  WaitForMultipleObjects(handle_count, handles, 1, INFINITE);
}

void thread_data_pool_free(ThreadDataPool *thread_pool) {
  for (size_t i = 0; i < thread_pool->max_size; ++i) {
    if (thread_pool->threads[i]->handle != NULL) {
      CloseHandle(thread_pool->threads[i]->handle);
    }
    free(thread_pool->threads[i]);
  }
  free(thread_pool->threads);
  free(thread_pool);
}
