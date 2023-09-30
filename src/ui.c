#include "ui.h"
#include "term_pos.h"

unsigned long __stdcall run_ui_loop(void *param)
{
  CONSOLE_SCREEN_BUFFER_INFO *a_cursor_buffer_info = NULL;
  a_cursor_buffer_info = (PCONSOLE_SCREEN_BUFFER_INFO)param;
  if (a_cursor_buffer_info == NULL)
  {
    return -1;
  }
  int exitFlag = 0;
  while (exitFlag <= 5)
  {
    printf(PRG_CLEAR_SCREEN);
    set_pos_middle_text(*a_cursor_buffer_info, "Hi!");
    Sleep(1000);
    exitFlag++;
  }
  return 0;
};

unsigned long init_terminal(void *handle)
{
  unsigned long old_mode = 0;
  if (!GetConsoleMode(handle, &old_mode))
  {
    errprint("Failed to get virtual terminal modes");
    exit(-1);
  }
  unsigned long new_mode = old_mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING |
                           DISABLE_NEWLINE_AUTO_RETURN;
  if (!SetConsoleMode(handle, new_mode))
  {
    errprint("Failed to set virtual terminal modes");
    exit(-1);
  };
  /* Enter Alternate Buffer */
  printf("\x1b[?1049h");
  return old_mode;
}

void end_terminal(void *handle, unsigned long mode)
{
  /* Exit Alternate Buffer */
  printf("\x1b[?1049l");
  SetConsoleMode(handle, mode);
}
