#include <stdlib.h>
#include <stdio.h>

#include <locale.h>
#include <ncurses.h>

#include <time.h>

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

/*
* t->mat4x4 =
*
* [ s*cos(a)  -s*sin(a) ]
* [ s*sin(a)   s*cos(a) ]
*
* m00 m01
* m10 m11
*/
void transform_update_mat(transform* t)
{
  float scale = t->scale;
  float angle = t->angle;
  t->rot_scale->m00 = scale*cos(angle);
  t->rot_scale->m01 = -scale*sin(angle);
  t->rot_scale->m10 = scale*sin(angle);
  t->rot_scale->m11 = scale*cos(angle);
}

void transform_set_angle(transform* t, float angle)
{
  t->angle = angle;
  transform_update_mat(t);
}

void transform_set_scale(transform* t, float scale)
{
  t->scale = scale;
  transform_update_mat(t);
}

void transform_displace(transform* t, float dx, float dy)
{
  t->translate->x += dx*cos(-t->angle) + dy*sin(-t->angle);
  t->translate->y += dx*cos(-t->angle + M_PI/2.) +
                                          dy*sin(-t->angle + M_PI/2.);
}

/*
 * Applies the inverse of the transformation to the vector
 */
void transform_apply_inv(transform* t, vec2* v)
{
  v->x = v->x - t->translate->x;
  v->y = v->y - t->translate->y;

  float det = (t->rot_scale->m00*t->rot_scale->m11 -
               t->rot_scale->m10*t->rot_scale->m01);
  float x = v->x * t->rot_scale->m11 - v->y * t->rot_scale->m01;
  float y = - v->x * t->rot_scale->m10 + v->y * t->rot_scale->m00;

  x /= det;
  y /= det;

  v->x = x;
  v->y = y;

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
  c->transform = transform_new();

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
  c->transform = transform_new();

  return c;
}

/* bitmap */

color bitmap_peek(component* c, vec2* v)
{
  v->y /= BLOCK_ASPECT;
  bitmap* b = c->fields;
  float im_vcoord_x = (v->x - b->x) / b->w;
  float im_vcoord_y = 1-(v->y - b->y) / b->h;
  if (im_vcoord_x >= 0 && im_vcoord_x < 1 && im_vcoord_y >= 0 &&
      im_vcoord_y < 1)
  {
    int img_x = (im_vcoord_x * b->img_width);
    int img_y = (im_vcoord_y * b->img_height);

    return b->pixels[img_x + b->img_width * img_y];
  }
  else
    return CLEAR;
}

color char_to_color(char c)
{
  switch (c)
  {
    case '0':
      return BLACK;
    case '1':
      return RED;
    case '2':
      return GREEN;
    case '3':
      return YELLOW;
    case '4':
      return BLUE;
    case '5':
      return MAGENTA;
    case '6':
      return CYAN;
    case '7':
      return WHITE;
  }
  return CLEAR;
}

component* bitmap_from_file(char* filename, component* dest)
{
  FILE* bmp_file = fopen(filename, "r");

  if (bmp_file == NULL)
  {
    ncknge_error("File not found: %s\n", filename);
  }

  int c = 0;
  int row_len = 0;
  int col_count = 0;
  int row_count = 0;

  while (c != EOF)
  {
    row_len = 0;
    while (c != 0xa && c != EOF)
    {
      row_len += 1;
      c = fgetc(bmp_file);
    }

    if (row_len > col_count)
    {
      col_count = row_len;
    }

    c = fgetc(bmp_file);
    row_count += 1;
  }

  int pix_count = row_count * col_count;
  color* pixels;
  if (dest == NULL)
  {
    pixels = malloc(pix_count * sizeof(color));
  }
  else
  {
    pixels = realloc(((bitmap*)dest->fields)->pixels,
        pix_count * sizeof(color));
  }

  rewind(bmp_file);
  c = fgetc(bmp_file);
  int i=0;

  int curr_row_size;
  while (c != EOF)
  {
    curr_row_size = 0;
    while (curr_row_size < col_count)
    {
      if (c != 0xa && c != EOF)
      {
        pixels[i] = char_to_color(c);
        c = fgetc(bmp_file);
      }
      else
      {
        pixels[i] = CLEAR;
      }

      curr_row_size += 1;
      i++;
    }
    c = fgetc(bmp_file);
  }

  fclose(bmp_file);

  component* cmp;
  bitmap* b;

  if (dest == NULL)
  {
    cmp = malloc(sizeof(component));

    b = malloc(sizeof(bitmap));

    cmp->fields = b;
    cmp->peek = bitmap_peek;
    cmp->transform = transform_new();
  }
  else
  {
    cmp = dest;
    b = dest->fields;
  }

  b->pixels = pixels;

  b->x = 0;
  b->y = 0;
  b->w = col_count;
  b->h = row_count;

  b->img_width = col_count;
  b->img_height = row_count;

  return cmp;
}

component* bitmap_create(int img_width, int img_height, char* img_str)
{

  component* c = malloc(sizeof(component));
  bitmap* b = malloc(sizeof(bitmap));

  b->x = 0;
  b->y = 0;
  b->w = img_width;
  b->h = img_height;

  b->img_width = img_width;
  b->img_height = img_height;

  b->pixels = malloc(sizeof(color) * img_width * img_height);

  int i;
  for (i=0; i < img_width * img_height; i ++)
  {
    b->pixels[i] = char_to_color(img_str[i]);
  }

  c->fields = b;
  c->peek = bitmap_peek;
  c->transform = transform_new();

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
        h.y *= BLOCK_ASPECT;

        /*
         * The order of the next two lines matters! They are not quite
         * linear transformations (translate is included).
         */

        /* Apply viewport transform */
        transform_apply(NCKNGE_GLOBAL_TRANSFORM, &h);

        /* Apply local transform */
        transform_apply_inv(c->transform, &h);

        color p = c->peek(c, &h);
        if (p != CLEAR)
          pix(x, y, p);
      }
    }
}

void pix(int x, int y, color color)
{
  /* The color pairs correspond to the color constants */
  color_set(color+1, NULL);

  mvaddch(NCKNGE_GLOBAL_SCREEN_INFO->rows-y-1, x, ' ');
}

struct timespec time_start;
struct timespec time_prev;
struct timespec time_now;

float elapsedTime()
{
  clock_gettime(CLOCK_MONOTONIC_RAW, &time_now);
  return time_now.tv_sec - time_start.tv_sec +
    (time_now.tv_nsec - time_start.tv_nsec)/1.e9;
}

float deltaTime()
{
  clock_gettime(CLOCK_MONOTONIC_RAW, &time_now);
  return time_now.tv_sec - time_prev.tv_sec +
    (time_now.tv_nsec - time_prev.tv_nsec)/1.e9;
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

  clock_gettime(CLOCK_MONOTONIC_RAW, &time_start);
  clock_gettime(CLOCK_MONOTONIC_RAW, &time_prev);

  char k;
  while (true)
  {
    draw();
    update();
    clock_gettime(CLOCK_MONOTONIC_RAW, &time_prev);

    k = getch();

    if (k == ERR)
    {
    }
    else if (k == -102) /* resize event */
    {
      NCKNGE_GLOBAL_SCREEN_INFO = screen_info_get();
    }
    else
    {
      key(k);
    }
  }

  /* @begin deinitialization */

  /*
   * @todo deallocate global objects
   * @body namely NCKNGE_GLOBAL_...
   */

  endwin();
}
