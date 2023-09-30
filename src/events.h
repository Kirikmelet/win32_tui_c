#ifndef PRG_EVENTS_H
#define PRG_EVENTS_H

#define PRG_EVENT_DEBUG 0x001

#include "utils.h"
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct event {
  unsigned short id;
} Event;

typedef struct event_queue {
  Event *queue;
  unsigned long index;
  unsigned long allocated_size;
} EventQueue;

typedef struct event_handler {
  EventQueue *event_queue;
  void *mutex_handle;
  unsigned int event_index;
} EventHandler;

EventHandler *GLOBAL_EVENT_HANDLER;

EventQueue *event_queue_init();

void event_queue_free(EventQueue *a_handler);

void event_queue_realloc(EventQueue *a_handler);

void event_queue_push(EventQueue *a_handler, Event event);

Event event_queue_read(EventQueue *a_handler);

EventHandler *event_handler_init();

void global_event_handler_init();

void global_event_handler_free();

void event_handler_free(EventHandler *a_handler);

void event_handler_add_event(EventHandler *a_handler, Event a_event);

Event event_handler_read_event(EventHandler *a_handler);

#endif
