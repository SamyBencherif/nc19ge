#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "ncknge.h"
#include <math.h>
#ifndef M_PI
  #define M_PI 3.1415926535897
#endif

component* frog;

void setup()
{
  transform_set_scale(camera, .3);
  /*
   * @todo seperate component_add funcs
   * I am planning to have two sister functions
   * screen_component_add
   * and
   * word_component_add
   */
  component_add(quad_new(0,0,4,4,WHITE));
  component_add(quad_new(8,0,4,4,WHITE));
  component_add(quad_new(0,8,4,4,WHITE));
  component_add(quad_new(8,8,4,4,WHITE));

  component_add(quad_new(5,0,2,2,RED));
  component_add(quad_new(0,5,2,2,BLUE));

  frog = component_add(ellipse_new(0,0,1,1, GREEN));

  frog->transform->translate->x = -3;
  frog->transform->translate->y = 3;

  camera->translate->x = frog->transform->translate->x;
  camera->translate->y = frog->transform->translate->y;
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
  if (k == 'w') {
    transform_displace(camera, 0, 1);
    transform_displace(frog->transform, 0, 1);
  }
  if (k == 's') {
    transform_displace(camera, 0, -1);
    transform_displace(frog->transform, 0, -1);
  }
  if (k == 'a') {
    transform_displace(camera, -1, 0);
    transform_displace(frog->transform, -1, 0);
  }
  if (k == 'd') {
    transform_displace(camera, 1, 0);
    transform_displace(frog->transform, 1, 0);
  }
  if (k == 'q') {
    transform_set_angle(camera, camera->angle + M_PI/12);
    transform_set_angle(frog->transform,
        frog->transform->angle + M_PI/12);
  }
  if (k == 'e') {
    transform_set_angle(camera, camera->angle - M_PI/12);
    transform_set_angle(frog->transform,
        frog->transform->angle - M_PI/12);
  }
  if (k == 'r') {
    transform_set_scale(camera, camera->scale/1.1);
  }
  if (k == 'f') {
    transform_set_scale(camera, camera->scale*1.1);
  }
}

int main(int argc, char** argv) {
  execute(setup, update, key);
  return EXIT_SUCCESS;
}
