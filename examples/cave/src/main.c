
#include <libgen.h>
#include <unistd.h>

#include <stdlib.h>

#include "ncknge.h"

#include "resource/KBM_CAVE.c"
#include "resource/KBM_WARRIOR.c"

component* cave;

component* warrior;

float warrior_vx = 0;
float warrior_vy = 0;

bool warrior_grounded = false;

void setup()
{
  cave = bitmap_create(KBM_CAVE_W, KBM_CAVE_H, KBM_CAVE);
  transform_set_scale(cave->transform, 3);
  cave->transform->translate->y = -((bitmap*)cave->fields)->img_height
                                            * BLOCK_ASPECT * 3;
  component_add(cave);

  warrior = bitmap_create(KBM_WARRIOR_W, KBM_WARRIOR_H, KBM_WARRIOR);

  warrior->transform->translate->y -= 5*BLOCK_ASPECT;

  warrior->transform->translate->x += 10;
  camera->translate->x += 10;

  warrior->transform->translate->y -= 30;
  camera->translate->y -= 30;

  component_add(warrior);
}

void warrior_physics()
{

  warrior->transform->translate->x += warrior_vx;
  camera->translate->x += warrior_vx;

  warrior_vx *= .9;

  if (warrior_vy >= -10)
  {
    warrior_vy -= .4;
  }

  warrior->transform->translate->y += warrior_vy;
  camera->translate->y += warrior_vy;

  warrior_grounded = false;
  while (
      peek_component(W/2 + 6.5, H/2 - 5, cave) == YELLOW
      )
  {
    warrior_grounded = true;
    warrior_vy = 0;
    warrior->transform->translate->y += 1;
    camera->translate->y += 1;
  }
}

void update()
{
  warrior_physics();
  print(3, H-4, MAGENTA, "       ");
  print(3, H-3, MAGENTA, "  HEY  ");
  print(3, H-2, MAGENTA, "       ");
}

void key(char k)
{
  if (k == 'w' || k == 3 || k == ' ')
  {
    if (warrior_grounded)
    {
      warrior_vy += 7;
    }
  }
  if (k == 'd' || k == 5)
  {
    warrior_vx = 3;
  }
  if (k == 'a' || k == 4)
  {
    warrior_vx = -3;
  }
}

int main(int argc, char** argv)
{
  chdir(dirname(argv[0]));
  execute(setup, update, key);
  return EXIT_SUCCESS;
}
