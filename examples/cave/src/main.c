
#include <libgen.h>
#include <unistd.h>

#include <stdlib.h>

#include "ncknge.h"

#include "resource/KBM_CAVE.c"
#include "resource/KBM_WARRIOR.c"

component* cave;
component* warrior;

component* coll_ind;

void setup()
{
  cave = bitmap_create(KBM_CAVE_W, KBM_CAVE_H, KBM_CAVE);
  transform_set_scale(cave->transform, 3);
  cave->transform->translate->y = -((bitmap*)cave->fields)->img_height
                                            * BLOCK_ASPECT * 3;
  component_add(cave);

  warrior = bitmap_create(KBM_WARRIOR_W, KBM_WARRIOR_H, KBM_WARRIOR);
  component_add(warrior);

  coll_ind = quad_new(0, 0, 1, BLOCK_ASPECT, GREEN);
  coll_ind->transform->translate->x = 6;
  coll_ind->transform->translate->y = 1;
  component_add(coll_ind);
}

void warrior_physics()
{
  print(0,0, peek_component(W/2 + 6, H/2 + 1, cave), "COLOR");
  if (
      peek_component(W/2 + 6, H/2 + 1, cave) == YELLOW
      )
  {
    ((quad*)coll_ind->fields)->color = RED;
  }
  else
  {
    ((quad*)coll_ind->fields)->color = GREEN;
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
  if (k == 'w')
  {
    warrior->transform->translate->y += 1;
    coll_ind->transform->translate->y += 1;
    camera->translate->y += 1;
  }
  if (k == 's')
  {
    warrior->transform->translate->y -= 1;
    coll_ind->transform->translate->y -= 1;
    camera->translate->y -= 1;
  }
}

int main(int argc, char** argv)
{
  chdir(dirname(argv[0]));
  execute(setup, update, key);
  return EXIT_SUCCESS;
}
