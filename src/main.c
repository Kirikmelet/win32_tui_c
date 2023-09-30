#include "main.h"
#include "events.h"
#include "thread.h"
#include "ui.h"
#include "utils.h"
#include <stdio.h>

void _test_event_func();

int main() {
  /*
   * Thread 0: UI
   * Thread 1: Input
   * Thread 2: IDK
   */
  ThreadDataPool *MAIN_THREAD_HANDLES = thread_data_pool_init(1);
  global_event_handler_init();
  if (MAIN_THREAD_HANDLES == NULL) {
    printf("oops");
    return -1;
  };
  CONSOLE_SCREEN_BUFFER_INFO info;
  void *handle = GetStdHandle(STD_OUTPUT_HANDLE);
  if (handle == INVALID_HANDLE_VALUE) {
    return -1;
  }
  unsigned long old_mode = init_terminal(handle);
  GetConsoleScreenBufferInfo(handle, &info);
  thread_data_pool_push_thread(MAIN_THREAD_HANDLES, run_ui_loop, &info);
  thread_data_pool_exec(MAIN_THREAD_HANDLES);
  thread_data_pool_free(MAIN_THREAD_HANDLES);
  MAIN_THREAD_HANDLES = NULL;
  end_terminal(handle, old_mode);
  CloseHandle(handle);
  global_event_handler_free();
  return 0;
}