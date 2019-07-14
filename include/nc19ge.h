
#include <stdbool.h>
#include <ncurses.h>

#define BLOCK_ASPECT (34./16)

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
} transform;

transform* transform_new();
void transform_apply(transform* t, vec2* v);

/* screen info */

typedef struct {
  int rows;
  int cols;
} screen_info;

/* view components */

typedef struct {
  int x;
  int y;
  int w;
  int h;
  int color;
} quad;

bool quad_contains_point(quad* q, vec2* v);

/* view model (uses view_components) */

typedef struct{
  void** items;
  int count;
} view_model;

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
