
#include <stdlib.h>
#include <stdio.h>

#include "nc19ge.h"
#include <math.h>
#ifndef M_PI
  #define M_PI 3.1415926535897
#endif

vec2* pos;
float angle = 0;
float scale = 1;

ellipse* frog;

void setup()
{
  pos = vec2_new(0, 0);

  transform_set(NC19GE_GLOBAL_TRANSFORM, pos, angle, scale);

  view_component_add(quad_new(0,0,4,4,YELLOW));
  view_component_add(quad_new(4,0,4,4,RED));
  view_component_add(quad_new(0,4,4,4,BLUE));
  frog = view_component_add(ellipse_new(0,0,4,1, GREEN));
}

void update()
{
  print(0, 0, "Use WASD to nudge translation.", 0);
  print(0, 1, "Use QE to adjust rotation.", 0);
  print(0, 2, "Use RF to set scale.", 0);

  char t[100];
  sprintf(t, "matrx [%f %f]",
      NC19GE_GLOBAL_TRANSFORM->rot_scale->m00,
      NC19GE_GLOBAL_TRANSFORM->rot_scale->m01
  );
  t[99] = '\0';
  print(0, 3, t, 0);

  sprintf(t, "      [%f %f]",
      NC19GE_GLOBAL_TRANSFORM->rot_scale->m10,
      NC19GE_GLOBAL_TRANSFORM->rot_scale->m11
  );
  t[99] = '\0';
  print(0, 4, t, 0);

  sprintf(t, "trnsl [%f %f]",
      NC19GE_GLOBAL_TRANSFORM->translate->x,
      NC19GE_GLOBAL_TRANSFORM->translate->y
  );
  t[99] = '\0';
  print(0, 6, t, 0);
}

void key(char k)
{
  /*
   * @todo objects should have their own transforms
   * @body thus would do away with most fields except for
   * the point test function and the color field. The trasform
   * would need to be inverse. I am thinking to inverse via
   * rot_scale analog, but matrix inversing might not be too
   * difficult either.
   *
   */
  if (k == 'w') {
    transform_translate(NC19GE_GLOBAL_TRANSFORM, vec2_new(0, 1));
    frog->y += 1;
  }
  if (k == 's') {
    transform_translate(NC19GE_GLOBAL_TRANSFORM, vec2_new(0, -1));
    frog->y -= 1;
  }
  if (k == 'a') {
    transform_translate(NC19GE_GLOBAL_TRANSFORM, vec2_new(-1, 0));
    frog->x -= 1;
  }
  if (k == 'd') {
    transform_translate(NC19GE_GLOBAL_TRANSFORM, vec2_new(1, 0));
    frog->x += 1;
  }
  if (k == 'q') {
    angle += M_PI/12;
  }
  if (k == 'e') {
    angle -= M_PI/12;
  }
  if (k == 'r') {
    scale += .1;
  }
  if (k == 'f') {
    scale -= .1;
  }

  transform_set(NC19GE_GLOBAL_TRANSFORM, pos, angle, scale);

}

int main(int argc, char** argv) {
  execute(setup, update, key);
  return EXIT_SUCCESS;
}
