
/* @begin data structures */

/* vec2 */

typedef struct {
  float x;
  float y;
} vec2;

vec2* vec2_zero();

/* mat4x4 */

typedef struct {
  float m00;
  float m01;
  float m10;
  float m11;
} mat4x4;

mat4x4* mat4x4_identity();

/* transform */

typedef struct {
  vec2* translate;
  mat4x4* rot_scale;
} transform;

transform* transform_new();

/* screen */

typedef struct {
  int rows;
  int cols;
  float aspect;
} screen_info;

/* view components */

typedef struct {
  int x;
  int y;
  int w;
  int h;
} quad;

/* view model (uses view_components) */

typedef struct{
  void** items;
  int count;
} view_model;

/* @end data structures */

transform* NC19GE_GLOBAL_TRANSFORM;
screen_info* NC19GE_GLOBAL_SCREEN_INFO;
view_model* NC19GE_GLOBAL_VIEW_MODEL;

/* Screen space blit a pixel. */
void pix(int x, int y);

void execute(void setup(), void update());
