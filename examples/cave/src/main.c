
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

  coll_ind = quad_new(6, 1, 1, BLOCK_ASPECT, YELLOW);
  component_add(coll_ind);
}

void warrior_physics()
{
  /**
   *
   * Extract function from ncknge draw, screen_point_color_from_obj,
   * rename if possible. This function will be used to tell if the
   * player's foot is touching yellow (from the cave).
   *
   */
  if (0)
  {
    ((quad*)coll_ind->fields)->color = RED;
  }
  else
  {
    ((quad*)coll_ind->fields)->color = YELLOW;
  }
}

void update()
{
  warrior_physics();
}

void key(char k)
{
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
