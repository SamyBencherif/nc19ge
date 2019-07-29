#include <stdlib.h>
#include <stdio.h>

#include <locale.h>
#include <ncurses.h>

#include <math.h>
#ifndef M_PI
  #define M_PI 3.1415926535897
#endif

#include "ncknge.h"

/* @begin data structures */

/* vec2 */

/*  @todo use compass rose
 *  In documentation, code, and constants refer to screenspace
 *  orientation and world space orientation with UP, RIGHT, LEFT,
 *  DOWN and NORTH, EAST, WEST, SOUTH respectively.
 */

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

transform* NCKNGE_GLOBAL_TRANSFORM;

transform* transform_new()
{
  transform* t;
  t = malloc(sizeof(transform));
  t->translate = vec2_zero();
  t->rot_scale = mat4x4_identity();
  t->angle = 0;
  t->scale = 1;

  return t;
}

/* DEPRECATED */
void transform_set(transform* t, vec2* pos, float angle, float scale)
{
  t->translate = pos;
  t->angle = angle;
  t->scale = scale;

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


/*
 * Applies the transformation to the vector
 */
void transform_apply(transform* t, vec2* v)
{

  /*
   * Stop. These lines are not independant.
   */
  float x = v->x * t->rot_scale->m00 + v->y * t->rot_scale->m01;
  float y = v->x * t->rot_scale->m10 + v->y * t->rot_scale->m11;
  v->x = x;
  v->y = y;

  v->x = v->x + t->translate->x;
  v->y = v->y + t->translate->y;
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

color quad_peek(component* c, vec2* v)
{
  quad* q = c->fields;
  if (q->x <= v->x && q->x + q->w > v->x &&
      q->y <= v->y && q->y + q->h > v->y)
    return q->color;
  else
    return CLEAR;
}

component* quad_new(float x, float y, float w, float h, color color)
{
  component* c = malloc(sizeof(component));

  quad* q = malloc(sizeof(quad));
  q->x = x;
  q->y = y;
  q->w = w;
  q->h = h;
  q->color = color;

  c->fields = q;
  c->peek = quad_peek;
  c->local_transform = transform_new();

  return c;
}

/* ellipse */

color ellipse_peek(component* c, vec2* v)
{
  ellipse* e = c->fields;
  if (pow(v->x - e->x, 2) / pow(e->w, 2) +
      pow(v->y - e->y, 2) / pow(e->h, 2) <= 1)
  {
    return e->color;
  }
  else
  {
    return CLEAR;
  }
}

component* ellipse_new(float x, float y, float w, float h, color color)
{
  component* c = malloc(sizeof(component));

  ellipse* e = malloc(sizeof(ellipse));
  e->x = x;
  e->y = y;
  e->w = w;
  e->h = h;
  e->color = color;

  c->fields = e;
  c->peek = ellipse_peek;
  c->local_transform = transform_new();

  return c;
}

void component_free(component* c)
{
  free(c->fields);
  free(c);
}

/* view model */


world_model* world_model_new()
{
  world_model* vm = malloc(sizeof(world_model));
  vm->head = NULL;
  vm->tail = NULL;
  return vm;
}

component* world_model_insert(world_model* vm, component* c)
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
  return c;
}

component* component_add(component* c)
{
  return world_model_insert(NCKNGE_GLOBAL_WORLD_MODEL, c);
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
  int x, y;
  for (x=0; x<NCKNGE_GLOBAL_SCREEN_INFO->cols; x++)
    for (y=0; y<NCKNGE_GLOBAL_SCREEN_INFO->rows; y++)
    {
      pix(
           x,
           y,
           COLOR_BLACK
         );

      component* c;
      /*
       * @todo rename VIEW_MODEL
       */
      for (
            c = NCKNGE_GLOBAL_WORLD_MODEL->tail;
            c != NULL;
            c = c->postrender
          )
      {
        /*
         * @todo optimize redraw
         * @body currently will set all pixels to the designated future
         * value, instead it should set only if the future value is
         * different from the present value.
         */

        /* Center world coords in screen */
        h.x = x - NCKNGE_GLOBAL_SCREEN_INFO->cols/2 + .5;
        h.y = y - NCKNGE_GLOBAL_SCREEN_INFO->rows/2 + .5;

        /* Perform aspect corrections */
        /* DEPRECATED (Currently set to multiply by 1)  */
        h.y *= BLOCK_ASPECT;

        /* Apply viewport transform */
        transform_apply(NCKNGE_GLOBAL_TRANSFORM, &h);

        /* Apply local transform */
        transform_apply(c->local_transform, &h);

        color p = c->peek(c, &h);
        if (p != CLEAR)
          pix(x, y, p);
      }
    }
}

void print(int x, int y, char* string, color color)
{
  /* color is ignored unless NGLB_COL_MOD is TEXT */
  color_set(color, NULL);

  mvaddstr(y, x, string);
}

void pix(int x, int y, color color)
{
  /* The color pairs correspond to the color constants */
  color_set(color+1, NULL);

  mvaddch(NCKNGE_GLOBAL_SCREEN_INFO->rows-y-1, x, ' ');
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

  NCKNGE_GLOBAL_TRANSFORM = transform_new();
  NCKNGE_GLOBAL_SCREEN_INFO = screen_info_get();
  NCKNGE_GLOBAL_WORLD_MODEL = world_model_new();

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
   * @body namely NCKNGE_GLOBAL_...
   */

  endwin();
}
