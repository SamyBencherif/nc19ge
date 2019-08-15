
#include <stdbool.h>
#include <stdlib.h>

#include <ncurses.h>

/* Set to 34/16 to perform aspect corrections */
#define BLOCK_ASPECT (34./16.)

#define W (NCKNGE_GLOBAL_SCREEN_INFO->cols)
#define H (NCKNGE_GLOBAL_SCREEN_INFO->rows)

#define ncknge_error(...) {\
  endwin(); \
  printf (__VA_ARGS__); \
  exit(1); \
}

#define print(x, y, color, ...) {\
  color_set(color+1, NULL); \
  mvprintw(y, x, __VA_ARGS__); \
}

/*
 * @todo ensure all colors are of type color
 * @body some may still be ints.
 */
typedef enum {
  CLEAR,
  BLACK = COLOR_BLACK,
  RED = COLOR_RED,
  GREEN = COLOR_GREEN,
  YELLOW = COLOR_YELLOW,
  BLUE = COLOR_BLUE,
  MAGENTA = COLOR_MAGENTA,
  CYAN = COLOR_CYAN,
  WHITE = COLOR_WHITE,
} color;

/* @begin data structures */

/* vec2 */

typedef struct {
  float x;
  float y;
} vec2;

vec2* vec2_zero();
vec2* vec2_new(float x, float y);

/* mat4x4 */

typedef struct {
  float m00;
  float m01;
  float m10;
  float m11;
} mat4x4;

/*
 * m00 m01
 * m10 m11
 */

mat4x4* mat4x4_identity();

/* transform */

typedef struct {
  vec2* translate;

  mat4x4* rot_scale;

  float angle;
  float scale;
} transform;

transform* transform_new();

void transform_set_angle(transform* t, float angle);
void transform_set_scale(transform* t, float scale);
void transform_displace(transform* t, float dx, float dy);

/* used to apply transform to imaginary camera */
void transform_apply(transform* t, vec2* v);

/* used to apply transform to component objects */
void transform_apply_inv(transform* t, vec2* v);

/* screen info */

typedef struct {
  int rows;
  int cols;
} screen_info;

/* view component */

typedef struct vc {
  color (*peek)(struct vc* c, vec2* v);
  void* fields;

  transform* transform;

  struct vc* prerender;
  struct vc* postrender;
} component;

/* specific view components */

/** quad **/

typedef struct {
  float x;
  float y;
  float w;
  float h;
  color color;
} quad;

color quad_peek(component* c, vec2* v);
component* quad_new(float x, float y, float w, float h, color color);
void quad_free(quad* q);

/** ellipse **/

typedef struct {
  float x;
  float y;
  float w;
  float h;
  color color;
} ellipse;

color ellipse_peek(component* c, vec2* v);
component* ellipse_new(float x, float y, float w, float h, color color);
void ellipse_free(ellipse* e);

/** bitmap **/

typedef struct {
  float x;
  float y;
  float w;
  float h;
  int img_width;
  int img_height;
  color* pixels;
} bitmap;

color bitmap_peek(component* c, vec2* v);
component* bitmap_from_file(char* filename, component* dest);
component* bitmap_create(int img_width, int img_height, char* img_str);
void bitmap_free(bitmap* b);

/* view model (uses components) */

typedef struct{
  component* head;
  component* tail;
} world_model;

world_model* world_model_new();
component* world_model_insert(world_model* vm, component* c);
void world_model_free(world_model* vm);

component* component_add(component* c);

typedef enum {
  BLOCK,
  TEXT
} color_mode;

/*
 * @todo include local ncursesw source
 */

/* @end data structures */

/*
 * @todo remove these from header
 * @body these structures should only be directly accessed from the
 * module itself.
 */
transform* NCKNGE_GLOBAL_TRANSFORM;
#define camera NCKNGE_GLOBAL_TRANSFORM

screen_info* NCKNGE_GLOBAL_SCREEN_INFO;
world_model* NCKNGE_GLOBAL_WORLD_MODEL;

/*
 * Default is BLOCK
 */
void set_color_mode(color_mode mode);

/* Screen space blit a pixel. */
void pix(int x, int y, color color);

float elapsedTime();

float deltaTime();

color peek_component(float x, float y, component* c);
color peek_world(float x, float y);

void execute(void setup(), void update(),
    void key(char k));
