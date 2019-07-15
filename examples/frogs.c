
#include <stdlib.h>
#include <stdio.h>

#include "nc19ge.h"
#include <math.h>

vec2* pos;
float angle = 0;
float scale = 1;

void setup()
{
  pos = vec2_new(0, 0);

  view_component_add(quad_new(0,0,4,4,YELLOW));
  view_component_add(quad_new(4,0,4,4,RED));
  view_component_add(quad_new(0,4,4,4,BLUE));
}

void update()
{
  print(0, 0, "Use WASD to nudge translation.", 0);
  print(0, 1, "Use QE to adjust rotation.", 0);
  print(0, 2, "Use RF to set scale.", 0);

  char t[100];
  snprintf(t, 100, "matrx [%f %f]\n      [%f %f]",
      NC19GE_GLOBAL_TRANSFORM->rot_scale->m00,
      NC19GE_GLOBAL_TRANSFORM->rot_scale->m01,
      NC19GE_GLOBAL_TRANSFORM->rot_scale->m10,
      NC19GE_GLOBAL_TRANSFORM->rot_scale->m11
  );
  print(0, 3, t, 0);

  snprintf(t, 100, "trnsl [%f %f]",
      NC19GE_GLOBAL_TRANSFORM->translate->x,
      NC19GE_GLOBAL_TRANSFORM->translate->y
  );
  print(0, 6, t, 0);
}

void key(char k)
{
  if (k == 'w')
    pos->y += 1;
  if (k == 's')
    pos->y -= 1;
  if (k == 'a')
    pos->x -= 1;
  if (k == 'd')
    pos->x += 1;
  if (k == 'q')
    angle += M_PI/12;
  if (k == 'e')
    angle -= M_PI/12;
  if (k == 'r')
    scale += .1;
  if (k == 'f')
    scale -= .1;

  transform_set(NC19GE_GLOBAL_TRANSFORM, pos, angle, scale);

}

int main(int argc, char** argv) {
  execute(setup, update, key);
  return EXIT_SUCCESS;
}
