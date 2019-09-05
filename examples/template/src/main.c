
#include "ncknge.h"

#include "resource/KBM_NCKNGE.c"

component* logo;

void setup()
{
  component_add(quad_new(-50, -20, 100, 10, WHITE));
  component_add(quad_new(-50, -10, 100, 10, MAGENTA));
  
  component_add(ellipse_new(24, 3, 10, 10, MAGENTA));

  logo = component_add(bitmap_create(KBM_NCKNGE_W, KBM_NCKNGE_H, KBM_NCKNGE));
  logo->transform->translate->x -= KBM_NCKNGE_W/2;
  logo->transform->translate->y -= KBM_NCKNGE_H/2 * BLOCK_ASPECT;

}

void update()
{
    print(W/2 - 40, H/2 + 3, MAGENTA, "NCurses Kinematic Normal Game Engine");
}

void key(char k)
{
}

int main(int argc, char** argv) {
  execute(setup, update, key);
  return EXIT_SUCCESS;
}
