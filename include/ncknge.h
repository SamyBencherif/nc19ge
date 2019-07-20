
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

  /*
   *  The 3 matrices shall be updated in tandom
   *  @todo (feature) add compile flag to spec which mats are needed
   *
   */

  mat4x4* rot; /* @todo implement */
  mat4x4* _scale; /* @todo implement */
  /*
   * float scale -> float zoom
   * mat4x4 _scale -> mat4x4 scale
   *
   *
   */

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
  /* @todo add transform here */

  /*
   * Local transforms can behave exactly like the global one.
   * Although functions like transform_translate which frame movements
   * as though they are movements of a camera would be less useful.
   *
   * I would rather think about moving and rotating the object in it's
   * own space, rather than a conceptual centered camera about it.
   *
   * This will require implementation of functions like
   * transform_inv_translate()
   *
   * which will simply invert the vector before applying it.
   *
   * maybe it is better to simply let the user include the required
   * negations.
   */

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

void* component_add(component* c);

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
world_model* NCKNGE_GLOBAL_VIEW_MODEL;

/*
 * Default is BLOCK
 */
void set_color_mode(color_mode mode);

void print(int x, int y, char* string, int color);

/* Screen space blit a pixel. */
void pix(int x, int y, int color);

void execute(void setup(), void update(), void key(char k));
