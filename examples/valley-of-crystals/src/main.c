
/* LIB */

#include <stdlib.h>

#include "ncknge.h"

#include <math.h>
#ifndef M_PI
  #define M_PI 3.1415926535897
#endif

/* ASSETS */

#include "resource/KBM_VALLEY_TITLE_0.c"
#include "resource/KBM_VALLEY_TITLE_1.c"
component* title_img_0;
component* title_img_1;

/* SCENES */

typedef enum {title, identity} scene;
scene present;

/* DATA */

int t = 0;

/* called before each scene */
void init()
{
    switch (present)
    {
        case title:

        title_img_0 = bitmap_create(KBM_VALLEY_TITLE_0_W,
                KBM_VALLEY_TITLE_0_H,
                KBM_VALLEY_TITLE_0);
        title_img_0->transform->translate->x = -KBM_VALLEY_TITLE_0_W/2;
        title_img_0->transform->translate->y = (-KBM_VALLEY_TITLE_0_H/2
                                                  + 2) * BLOCK_ASPECT;
        component_add(title_img_0);

        title_img_1 = bitmap_create(KBM_VALLEY_TITLE_1_W,
                KBM_VALLEY_TITLE_1_H,
                KBM_VALLEY_TITLE_1);
        title_img_1->transform->translate->x = -KBM_VALLEY_TITLE_1_W/2;
        title_img_1->transform->translate->y = (-KBM_VALLEY_TITLE_1_H/2
                                                  + 2) * BLOCK_ASPECT;
        title_img_1->visible = false;
        component_add(title_img_1);

        break;
        case identity:
        /* remove title image */
        component_remove(title_img_0);
        component_remove(title_img_1);
        break;
    }
}

void update()
{
    switch (present)
    {
        case title:

        print(W/2 - 14, H/2 + 6, BLACK, "~ Press Any Key To Begin ~");

        if (t%5 == 0)
        {
            title_img_0->visible = !title_img_0->visible;
            title_img_1->visible = !title_img_1->visible;
        }

        break;
        case identity:
        print(0,0,BLACK,"Choose an identity.");
        print(0,2,BLACK,"I am a loser.");
        print(0,3,WHITE,"I am a cool guy.");
        break;
        default:
        break;
    }
    t++;
}

void setup()
{
    present = title;
    init();
}

void key(char k)
{
    switch (present)
    {
        case title:
        present = identity;
        init();
        break;
        default:
        break;
    }
}

int main(int argc, char** argv) {
  execute(setup, update, key);
  return EXIT_SUCCESS;
}
