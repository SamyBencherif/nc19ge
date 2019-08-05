#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "ncknge.h"
#include <math.h>
#ifndef M_PI
  #define M_PI 3.1415926535897
#endif

component* myBMP;
float ttr;

void setup()
{
  myBMP = bitmap_from_file("img/tester.kbm", NULL);
  component_add(myBMP);
  transform_set_scale(camera, 1);

  ttr = 5;
}

void update()
{
  print(0, 0, BLACK, "Use WASD to nudge translation.");
  print(0, 1, BLACK, "Use QE to adjust rotation.");
  print(0, 2, BLACK, "Use RF to set scale.");

  if (ttr <= 3)
  {
    print(0, 5, YELLOW, "Reloading in %d...", (int) (ttr + .5));
  }

  ttr -= deltaTime();
  if (ttr <= 0)
  {
    bitmap_from_file("img/tester.kbm", myBMP);
    ttr = 5;
  }
}

void key(char k)
{
  if (k == 'w') {
    transform_displace(camera, 0, 1);
  }
  if (k == 's') {
    transform_displace(camera, 0, -1);
  }
  if (k == 'a') {
    transform_displace(camera, -1, 0);
  }
  if (k == 'd') {
    transform_displace(camera, 1, 0);
  }
  if (k == 'q') {
    transform_set_angle(camera, camera->angle + M_PI/12);
  }
  if (k == 'e') {
    transform_set_angle(camera, camera->angle - M_PI/12);
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
