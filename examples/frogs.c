
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

  NC19GE_GLOBAL_VIEW_MODEL = malloc(sizeof(NC19GE_GLOBAL_VIEW_MODEL));
  NC19GE_GLOBAL_VIEW_MODEL->items = malloc(1*sizeof(void*));
  NC19GE_GLOBAL_VIEW_MODEL->count = 1;

  quad* Q = malloc(sizeof(quad));
  Q->x = 0;
  Q->y = 0;
  Q->w = 4;
  Q->h = 4;
  Q->color = COLOR_GREEN;
  NC19GE_GLOBAL_VIEW_MODEL->items[0] = Q;

}

void update()
{
  print(0, 0, "Use WASD to nudge translation.", 0);
  print(0, 1, "Use QE to adjust rotation.", 0);
  print(0, 2, "Use RF to set scale.", 0);

  char t[100];
  snprintf(t, 100, "matrx [%f %f ; %f %f]",
      NC19GE_GLOBAL_TRANSFORM->rot_scale->m00,
      NC19GE_GLOBAL_TRANSFORM->rot_scale->m01,
      NC19GE_GLOBAL_TRANSFORM->rot_scale->m10,
      NC19GE_GLOBAL_TRANSFORM->rot_scale->m11
  );
  print(0, 3, t, 0);
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
    angle += M_PI/6;
  if (k == 'e')
    angle -= M_PI/6;
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
