
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

  transform* local_transform;

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

/* @end data structures */

/*
 * @todo remove these from header
 * @body these structures should only be directly accessed from the
 * module itself.
 */
transform* NCKNGE_GLOBAL_TRANSFORM;
screen_info* NCKNGE_GLOBAL_SCREEN_INFO;
world_model* NCKNGE_GLOBAL_WORLD_MODEL;

/*
 * Default is BLOCK
 */
void set_color_mode(color_mode mode);

void print(int x, int y, char* string, color color);

/* Screen space blit a pixel. */
void pix(int x, int y, color color);

void execute(void setup(), void update(), void key(char k));
