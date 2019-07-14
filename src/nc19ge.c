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
}

void quad(float x, float y, float w, float h)
{
  /*
   * This function will need to update some kind of data structure that
   * can keep track of boundary collisions for pixel-by-pixel StoW
   * projection.
   *
   * actually... that's retarded. I need to go ahead and know which
   * pixels need changing and only update those ones.
   *
   * ah but here's the thing. redraw can occur over translation OR
   * the initial draw. So i need a way to compute update pixels in
   * a general case.
   *
   * I'm thinking that must be the data structure. The information
   * must be stored so a translate can add and remove objects from the
   * screen. In theory, a very large view model can have some
   * components that are offloaded into a file (thanks to the
   * linearity of our transforms)
   */

  /*
   *  pseudo-code
   *  1. Update View Model (data structure)
   *  2. Request Redraw
   *
   *  this is to reduce redundancy in the apply translation method
   *  which also must be implemented.
   */
}

void pix(float x, float y)
{
  mvaddch(10, 10, '@');
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
