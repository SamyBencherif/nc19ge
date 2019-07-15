
#include <stdbool.h>
#include <ncurses.h>

/* Set to 34/16 to perform aspect corrections */
#define BLOCK_ASPECT 1


/*
 * @todo ensure all colors are of type color
 * @body some may still be ints.
 */
typedef enum {
  BLACK = COLOR_BLACK,
  RED = COLOR_RED,
  GREEN = COLOR_GREEN,
  YELLOW = COLOR_YELLOW,
  BLUE = COLOR_BLUE,
  MAGENTA = COLOR_MAGENTA,
  CYAN = COLOR_CYAN,
  WHITE = COLOR_WHITE,
  CLEAR
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

void transform_set(transform* t, vec2* pos, float angle, float scale);
void transform_translate(transform* t, vec2* v);
void transform_apply(transform* t, vec2* v);

/* screen info */

typedef struct {
  int rows;
  int cols;
} screen_info;

/* view component */

typedef struct vc {
  color (*peek)(struct vc* c, vec2* v);
  void* fields;
  struct vc* prerender;
  struct vc* postrender;
} view_component;

/* specific view components */

    /** quad **/

typedef struct {
  float x;
  float y;
  float w;
  float h;
  color color;
} quad;

color quad_peek(view_component* c, vec2* v);
view_component* quad_new(float x, float y, float w, float h, color color);

    /** ellipse **/

typedef struct {
  float x;
  float y;
  float w;
  float h;
  color color;
} ellipse;

color ellipse_peek(view_component* c, vec2* v);
view_component* ellipse_new(float x, float y, float w, float h, color color);

/* view model (uses view_components) */

typedef struct{
  view_component* head;
  view_component* tail;
} view_model;

view_model* view_model_new();
view_component* view_model_insert(view_model* vm, view_component* c);
void view_model_free(view_model* vm);

void* view_component_add(view_component* c);

typedef enum {
  BLOCK,
  TEXT
} color_mode;

/* @end data structures */

/*
 * @todo remove these from header
 * @body these structures should only be directly accessed from the
 * module itself.
 */
transform* NC19GE_GLOBAL_TRANSFORM;
screen_info* NC19GE_GLOBAL_SCREEN_INFO;
view_model* NC19GE_GLOBAL_VIEW_MODEL;

/*
 * Default is BLOCK
 */
void set_color_mode(color_mode mode);

void print(int x, int y, char* string, int color);

/* Screen space blit a pixel. */
void pix(int x, int y, int color);

void execute(void setup(), void update(), void key(char k));
