#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "ncknge.h"
#include <math.h>
#ifndef M_PI
  #define M_PI 3.1415926535897
#endif

float random_float()
{
  return (float)rand()/RAND_MAX;
}

int random_int(int x)
{
  return rand() % x;
}

component* frog1;
component* frog2;

float fly_vx = 0;
float fly_vy = 0;

component* fly;
bitmap flyFrames[2];

void setup()
{
  component_add(quad_new(-50,-10,100,10,MAGENTA));
  component_add(quad_new(-50,-20,100,10,WHITE));

  frog1 = component_add(bitmap_from_file("tex/frog.kbm", NULL));
  frog1->transform->translate->x = 14;
  frog1->transform->translate->y = -2;

  frog2 = component_add(bitmap_from_file("tex/frog.kbm", NULL));
  frog2->transform->translate->x = -22;
  frog2->transform->translate->y = -6;

  /* matrix hack, flips horizontally */
  frog2->transform->rot_scale->m00 *= -1;

  fly = component_add(bitmap_from_file("tex/fly2.kbm", NULL));
  flyFrames[1] = *(bitmap*)fly->fields;
  bitmap_from_file("tex/fly.kbm", fly);
  flyFrames[0] = *(bitmap*)fly->fields;

  camera->translate->y = 10;
}

void update()
{
  fly->fields = (void*)&flyFrames[ ( (int) elapsedTime() ) % 2 ];
  fly->transform->translate->x += fly_vx;
  fly->transform->translate->y += fly_vy;

  int d = random_int(4);

  if (d == 0)
  {
    fly_vy = 1;
  }
  if (d == 1)
  {
    fly_vy = -1;
  }
  if (d == 2)
  {
    fly_vx = -1;
  }
  if (d == 3)
  {
    fly_vx = 1;
  }

  if (fly->transform->translate->y < -10)
  {
    fly_vy = 1;
  }
  if (fly->transform->translate->y > 30)
  {
    fly_vy = -1;
  }
  if (fly->transform->translate->x > 40)
  {
    fly_vx = -1;
  }
  if (fly->transform->translate->x < -40)
  {
    fly_vx = 1;
  }
}

void key(char k)
{
}

int main(int argc, char** argv) {
  execute(setup, update, key);
  return EXIT_SUCCESS;
}
