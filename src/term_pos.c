#include "term_pos.h"
#include "utils.h"
#include <stdio.h>

void set_pos_middle_text(CONSOLE_SCREEN_BUFFER_INFO a_cursor_buffer_info,
                         const char *a_text)
{
  SMALL_RECT window = a_cursor_buffer_info.srWindow;
  short top = window.Top;
  short bottom = window.Bottom;
  short left = window.Left;
  short right = window.Right;
  short middle_y = top + bottom / 2;
  short middle_x = left + right / 2;
  printf("\x1b[%i;%iH", middle_y, middle_x);
  printf("%s", a_text);
}
void draw_box(RECT a_coords)
{
}
