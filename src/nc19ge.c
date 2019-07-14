#include <stdlib.h>
#include <stdio.h>

#include <locale.h>
#include <ncurses.h>

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

vec2* vec2_new(float x, float y)
{
  vec2* v;
  v = malloc(sizeof(vec2));
  v->x = x;
  v->y = y;
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

void transform_apply(transform* t, vec2* v)
{
  float x = v->x * t->rot_scale->m00 + v->y * t->rot_scale->m01;
  float y = v->x * t->rot_scale->m10 + v->y * t->rot_scale->m11;
  v->x = x + t->translate->x;
  v->y = y + t->translate->y;
}

void transform_free(transform* t)
{
  free(t->translate);
  free(t->rot_scale);
  free(t);
}

/* screen info */

screen_info* screen_info_get()
{
  int x;
  int y;
  getmaxyx(stdscr, y, x);
  screen_info* si = malloc(sizeof(screen_info));
  si->cols = x;
  si->rows = y;

  return si;
}

/* quad */

bool quad_contains_point(quad* q, vec2* v)
{
  return q->x <= v->x && q->x + q->w > v->x &&
         q->y <= v->y && q->y + q->h > v->y;
}

/* view model */

void view_model_free(view_model* vm)
{
  for (int i=0; i<vm->count; i++)
  {
    free(vm->items[i]);
  }
  free(vm);
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

  vec2 h;
  for (int x=0; x<NC19GE_GLOBAL_SCREEN_INFO->cols; x++)
    for (int y=0; y<NC19GE_GLOBAL_SCREEN_INFO->rows; y++)
    {
      /* Center world coords in screen */
      h.x = x - NC19GE_GLOBAL_SCREEN_INFO->cols/2;
      h.y = y - NC19GE_GLOBAL_SCREEN_INFO->rows/2;

      /* Perform aspect corrections */
      h.y *= BLOCK_ASPECT;

      /* Apply view port transformation */
      transform_apply(NC19GE_GLOBAL_TRANSFORM, &h);

      for (int i=0; i<NC19GE_GLOBAL_VIEW_MODEL->count; i++)
      {
        quad* q = NC19GE_GLOBAL_VIEW_MODEL->items[i];

        if (quad_contains_point(q, &h))
          pix(
               x,
               y
             );
      }
    }
}

void pix(int x, int y)
{
  mvaddstr(NC19GE_GLOBAL_SCREEN_INFO->rows-y-1, x, "█");
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
  NC19GE_GLOBAL_SCREEN_INFO = screen_info_get();

  setup();

  char k;
  k = 0;
  while (true)
  {
    draw();
    update();

    k = getch();

    /*
     * @todo on resize, update_screen_info
     * @body to ensure things that are supposed to be centered stay
     * centered
     */
  }

  /* @begin deinitialization */

  endwin();
}
