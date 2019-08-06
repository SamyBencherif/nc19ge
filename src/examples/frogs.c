#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "ncknge.h"
#include <math.h>
#ifndef M_PI
  #define M_PI 3.1415926535897
#endif

component* frog1;
component* frog2;
component* fly;

void setup()
{
  component_add(quad_new(-50,-10,100,10,RED));
  component_add(quad_new(-50,-20,100,10,WHITE));

  frog1 = component_add(bitmap_from_file("tex/frog.kbm", NULL));
  frog1->transform->translate->x = 10;
  frog1->transform->translate->y = -2;

  frog2 = component_add(bitmap_from_file("tex/frog.kbm", NULL));
  frog2->transform->translate->x = 0;

  camera->translate->y = 10;
}

void update()
{
}

void key(char k)
{
  if (k == 'w')
  {
    frog2->transform->translate->y -= 1;
  }
}

int main(int argc, char** argv) {
  execute(setup, update, key);
  return EXIT_SUCCESS;
}
