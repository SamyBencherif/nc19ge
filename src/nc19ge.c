#include <stdlib.h>
#include <stdio.h>

#include <locale.h>
#include <curses.h>

#include "nc19ge.h"

/* @begin data structures */

/* vec2 */

vec2* vec2_zero()
{
  vec2* v;
  v = malloc(sizeof(vec2));
  v->x = 0;
  v->y = 0;
  return v;
}

/* mat4x4 */
mat4x4* mat4x4_identity()
{
  mat4x4* m;
  m = malloc(sizeof(mat4x4));
  m->m00 = 1;
  m->m01 = 0;
  m->m10 = 0;
  m->m11 = 1;

  return m;
}

/* transform */

transform* NC19GE_GLOBAL_TRANSFORM;

transform* transform_new()
{
  transform* t;
  t = malloc(sizeof(transform));
  t->translate = vec2_zero();
  t->rot_scale = mat4x4_identity();

  return t;
}

screen_info* screen_info_get()
{
  int x;
  int y;
  getmaxyx(stdscr, y, x);
  screen_info* si = malloc(sizeof(screen_info));
}

/* @end data structures */

void draw()
{
  /*
   * this essential function takes two global objects, the view model,
   * and the transform and produces the necessary minimal draw.
   *
   * (also needs prev model + transform or something)
   *
   */

  for (int i=0; i<NC19GE_GLOBAL_VIEW_MODEL->count; i++)
  {
    NC19GE_GLOBAL_VIEW_MODEL->items[i]
  }

}


void pix(int x, int y)
{
  mvaddch(x, y, '@');
}

void execute(void setup(), void update())
{
  setlocale(LC_ALL, "");

  initscr();
  cbreak();
  noecho();

  nonl();
  intrflush(stdscr, FALSE);
  keypad(stdscr, TRUE);

  /* halfdelay to FPS table
   *
   * hd | fps
   * ---+----
   *  1 |  10
   *  2 |   5
   *  3 |  3.
   *  4 |  3.
   *  5 |   2
   *
   * */
  halfdelay(1);

  /* NCURSES is initialized */

  NC19GE_GLOBAL_TRANSFORM = transform_new();

  setup();

  char k;
  k = 0;
  while (true)
  {
    update();
    k = getch();
  }

  /* @begin deinitialization */

  endwin();
}
