
#include <stdlib.h>
#include <stdio.h>

#include "ncknge.h"
#include <math.h>
#ifndef M_PI
  #define M_PI 3.1415926535897
#endif

vec2* pos;
float angle = 0;
float scale = 1;

component* frog;

void setup()
{
  pos = vec2_new(0, 0);

  transform_set(NCKNGE_GLOBAL_TRANSFORM, pos, angle, scale);

  /*
   * I am planning to have two sister functions
   * screen_component_add
   * and
   * word_component_add
   */
  component_add(quad_new(0,0,4,4,YELLOW));
  component_add(quad_new(4,0,4,4,RED));
  component_add(quad_new(0,4,4,4,BLUE));
  frog = component_add(ellipse_new(0,0,4,1, GREEN));
}

void update()
{
  print(0, 0, "Use WASD to nudge translation.", 0);
  print(0, 1, "Use QE to adjust rotation.", 0);
  print(0, 2, "Use RF to set scale.", 0);

  char t[100];
  sprintf(t, "matrx [%f %f]",
      NCKNGE_GLOBAL_TRANSFORM->rot_scale->m00,
      NCKNGE_GLOBAL_TRANSFORM->rot_scale->m01
  );
  t[99] = '\0';
  print(0, 3, t, 0);

  sprintf(t, "      [%f %f]",
      NCKNGE_GLOBAL_TRANSFORM->rot_scale->m10,
      NCKNGE_GLOBAL_TRANSFORM->rot_scale->m11
  );
  t[99] = '\0';
  print(0, 4, t, 0);

  sprintf(t, "trnsl [%f %f]",
      NCKNGE_GLOBAL_TRANSFORM->translate->x,
      NCKNGE_GLOBAL_TRANSFORM->translate->y
  );
  t[99] = '\0';
  print(0, 6, t, 0);
}

void key(char k)
{
  /*
   * With new language, it is clear that the frog is moving
   * North instead of UP when I press w
   */
  if (k == 'w') {
    transform_translate(NCKNGE_GLOBAL_TRANSFORM, vec2_new(0, 1));

    /*  After implementing local translations and other considerations,
     *  this code should become
     *
     *  (camera is a macro for NCKNGE_GLOBAL_TRANSFORM)
     *
     *  transform_translate(camera, UP);
     *  transform_itranslate(frog->transform, UP);
     *
     *  @todo delete issue about removing GLOBALS from ncknge header
     *  they are now to be used in client code, via macros
     *
     */
  }
  if (k == 's') {
    transform_translate(NCKNGE_GLOBAL_TRANSFORM, vec2_new(0, -1));
  }
  if (k == 'a') {
    transform_translate(NCKNGE_GLOBAL_TRANSFORM, vec2_new(-1, 0));
  }
  if (k == 'd') {
    transform_translate(NCKNGE_GLOBAL_TRANSFORM, vec2_new(1, 0));
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

  transform_set(NCKNGE_GLOBAL_TRANSFORM, pos, angle, scale);
  transform_set(frog->local_transform, pos, angle, scale);

}

int main(int argc, char** argv) {
  execute(setup, update, key);
  return EXIT_SUCCESS;
}
