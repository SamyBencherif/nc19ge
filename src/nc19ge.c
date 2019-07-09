
#include <stdio.h>
#include <locale.h>
#include <curses.h>

void execute()
{
  setlocale(LC_ALL, "");

  initscr();
  cbreak();
  noecho();

  nonl();
  intrflush(stdscr, FALSE);
  keypad(stdscr, TRUE);

  getch();

  endwin();

}
