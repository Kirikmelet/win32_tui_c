#ifndef P_TERM_POS

#define P_TERM_POS
#include "utils.h"
#include <Windows.h>
#include <stdio.h>

void set_pos_middle_text(CONSOLE_SCREEN_BUFFER_INFO a_cursor_buffer_info,
                         const char *a_text);

void draw_box(RECT a_coords);
#endif
