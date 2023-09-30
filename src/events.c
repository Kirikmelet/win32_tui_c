#include "events.h"

EventQueue *event_queue_init() {
  EventQueue *queue = malloc(sizeof(EventQueue));
  if (queue == NULL) {
    errprint("Failed to malloc memory!");
    return NULL;
  }
  queue->index = 0;
  queue->allocated_size = 150;
  queue->queue = calloc(sizeof(Event), queue->allocated_size);
  return queue;
}

void event_queue_free(EventQueue *a_handler) { free(a_handler->queue); }
void event_queue_push(EventQueue *a_handler, Event event) {
  if (a_handler->index >= a_handler->allocated_size) {
    event_queue_realloc(a_handler);
  }
  a_handler->queue[a_handler->index++] = event;
}

Event event_queue_read(EventQueue *a_handler) {
  return a_handler->queue[--a_handler->index];
}

void event_queue_realloc(EventQueue *a_handler) {
  a_handler->allocated_size += 150;
  a_handler->queue = realloc(a_handler->queue, a_handler->allocated_size);
}

EventHandler *event_handler_init() {
  EventHandler *handler = malloc(sizeof(EventHandler));
  if (handler == NULL) {
    errprint("Failed to malloc memory!");
    return NULL;
  }
  handler->event_queue = event_queue_init();
  handler->mutex_handle = CreateMutexA(0, 0, "event_handler");
  handler->event_index = 0;
  return handler;
}

void global_event_handler_init() {
  GLOBAL_EVENT_HANDLER = event_handler_init();
}

void global_event_handler_free() {
  event_handler_free(GLOBAL_EVENT_HANDLER);
}

void event_handler_free(EventHandler *a_handler) {
  event_queue_free(a_handler->event_queue);
  CloseHandle(a_handler->mutex_handle);
}

void event_handler_add_event(EventHandler *a_handler, Event event) {
  unsigned long mutex_result =
      WaitForSingleObject(a_handler->mutex_handle, INFINITE);
  switch (mutex_result) {
  case WAIT_OBJECT_0:
    __try {
      event_queue_push(a_handler->event_queue, event);
    } __finally {
      if (!ReleaseMutex(a_handler->mutex_handle)) {
      }
    }
    break;
  case WAIT_ABANDONED:
    break;
  };
}

Event event_handler_read_event(EventHandler *a_handler) {
  Event event;
  unsigned long mutex_result =
      WaitForSingleObject(a_handler->mutex_handle, INFINITE);
  switch (mutex_result) {
  case WAIT_OBJECT_0:
    __try {
      event = event_queue_read(a_handler->event_queue);
    } __finally {
      if (!ReleaseMutex(a_handler->mutex_handle)) {
      }
    }
    break;
  case WAIT_ABANDONED:
    break;
  };
  return event;
}
