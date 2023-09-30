#ifndef PRG_MACROS_H
#define PRG_MACROS_H
#define ESC_ANSI "\x1b["
#define errprint(x) fprintf(stderr, "ERROR: " x "\n")
#define ansiprint(x) fprintf(stdout, "\x1b" x "\n")
#define ansicolorprint(x) ansiprint("[" x)
#endif
