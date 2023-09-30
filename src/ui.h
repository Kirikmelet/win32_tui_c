#ifndef P_UI_H
#define P_UI_H
#include "term_pos.h"
#include "utils.h"
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

#define CUM_SEX "\x1b["
#define PRG_CLEAR_SCREEN CUM_SEX "2J\n"

unsigned long __stdcall run_ui_loop(void *param);

unsigned long init_terminal(void *handle);

void end_terminal(void *handle, unsigned long mode);

#endif
