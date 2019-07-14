
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

/* @end data structures */

transform* NC19GE_GLOBAL_TRANSFORM;
screen_info* NC19GE_GLOBAL_SCREEN_INFO;

void quad(float x, float y, float w, float h);

void pix(float x, float y);

void execute(void setup(), void update);
