#include <stdlib.h>
#include <stdio.h>

#include <locale.h>
#include <ncurses.h>

#include <math.h>

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

void transform_set(transform* t, vec2* pos, float angle, float scale)
{
  t->translate = pos;

  /*
   * t->mat4x4 =
   *
   * [ s*cos(a)  -s*sin(a) ]
   * [ s*sin(a)   s*cos(a) ]
   *
   * m00 m01
   * m10 m11
   */

  t->rot_scale->m00 = scale*cos(angle);
  t->rot_scale->m01 = -scale*sin(angle);
  t->rot_scale->m10 = scale*sin(angle);
  t->rot_scale->m11 = scale*cos(angle);

}

void transform_apply(transform* t, vec2* v)
{
  v->x = v->x + t->translate->x;
  v->y = v->y + t->translate->y;

  /*
   * Stop. These lines are not independant.
   */
  float x = v->x * t->rot_scale->m00 + v->y * t->rot_scale->m01;
  float y = v->x * t->rot_scale->m10 + v->y * t->rot_scale->m11;
  v->x = x;
  v->y = y;
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

color quad_peek(view_component* c, vec2* v)
{
  quad* q = c->fields;
  if (q->x <= v->x && q->x + q->w > v->x &&
      q->y <= v->y && q->y + q->h > v->y)
    return q->color;
  else
    return CLEAR;
}

view_component* quad_new(float x, float y, float w, float h, color color)
{
  view_component* c = malloc(sizeof(view_component));

  quad* q = malloc(sizeof(quad));
  q->x = x;
  q->y = y;
  q->w = w;
  q->h = h;
  q->color = color;

  c->fields = q;
  c->peek = quad_peek;

  return c;
}

void view_component_free(view_component* c)
{
  free(c->fields);
  free(c);
}

/* view model */


view_model* view_model_new()
{
  view_model* vm = malloc(sizeof(view_model));
  vm->head = NULL;
  vm->tail = NULL;
  return vm;
}

void view_model_insert(view_model* vm, view_component* c)
{
  if (vm->head == NULL)
  {
    vm->head = c;
    vm->tail = c;
  }
  else
  {
    c->prerender = vm->head;
    vm->head->postrender = c;
    vm->head = c;
  }
}

void view_component_add(view_component* c)
{
  view_model_insert(NC19GE_GLOBAL_VIEW_MODEL, c);
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

      pix(
           x,
           y,
           COLOR_BLACK
         );

      view_component* c;
      for (
            c = NC19GE_GLOBAL_VIEW_MODEL->tail;
            c != NULL;
            c = c->postrender
          )
      {
        /*
         * @todo optimize redraw
         * @body currently will set all pixels to the designated future value, instead it should set only if the future value is different from the present value.
         * @body here is a second line.
         */

        color p = c->peek(c, &h);
        if (p != CLEAR)
          pix(x, y, p);
      }
    }
}

void print(int x, int y, char* string, int color)
{
  /* color is ignored unless NGLB_COL_MOD is TEXT */
  color_set(1, NULL);

  mvaddstr(y, x, string);
}

void pix(int x, int y, int color)
{
  /* The color pairs correspond to the color constants */
  color_set(color+1, NULL);

  mvaddch(NC19GE_GLOBAL_SCREEN_INFO->rows-y-1, x, ' ');
}

void execute(void setup(), void update(), void key(char k))
{
  setlocale(LC_ALL, "");

  initscr();
  start_color();

  cbreak();
  noecho();

  /* hide cursor */
  curs_set(0);

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

  /* Color config */

  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_RED);
  init_pair(3, COLOR_BLACK, COLOR_GREEN);
  init_pair(4, COLOR_BLACK, COLOR_YELLOW);
  init_pair(5, COLOR_BLACK, COLOR_BLUE);
  init_pair(6, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(7, COLOR_BLACK, COLOR_CYAN);
  init_pair(8, COLOR_BLACK, COLOR_WHITE);

  /* NCURSES is initialized */

  NC19GE_GLOBAL_TRANSFORM = transform_new();
  NC19GE_GLOBAL_SCREEN_INFO = screen_info_get();
  NC19GE_GLOBAL_VIEW_MODEL = view_model_new();

  setup();

  char k;
  while (true)
  {
    draw();
    update();

    k = getch();

    if (k != ERR)
    {
      key(k);
    }

    /*
     * @todo on resize, update_screen_info
     * @body to ensure things that are supposed to be centered stay
     * centered
     */
  }

  /* @begin deinitialization */

  /*
   * @todo deallocate global objects
   * @body namely NC19GE_GLOBAL_...
   */

  endwin();
}
