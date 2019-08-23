#include <stdlib.h>
#include <stdio.h>

#include <libgen.h>
#include <unistd.h>

#include "ncknge.h"

#include <math.h>
#ifndef M_PI
  #define M_PI 3.1415926535897
#endif

#define number_of_slides 3

/* list all included sldes */
#include "resource/KBM_SLIDE1.c"
#include "resource/KBM_SLIDE2.c"
#include "resource/KBM_SLIDE3.c"

component* slides[number_of_slides];

int slidecurrent;
int time;

float angle;
float scale;

#define load_slide(n) {\
  slides[n-1] = bitmap_create(KBM_SLIDE##n##_W, KBM_SLIDE##n##_H, KBM_SLIDE##n); \
  slides[n-1]->transform->translate->x = -KBM_SLIDE##n##_W/2; \
  slides[n-1]->transform->translate->y = -KBM_SLIDE##n##_H/2*BLOCK_ASPECT; \
  slides[n-1]->visible = false; \
  component_add(slides[n-1]); \
}

void setup()
{
  slidecurrent = 0;
  time = 0;

  angle = 0;
  scale = 1;
 
  /* this is a macro, cannot be put in loop
     should load all slides from `number_of_slides` */
  load_slide(1);
  load_slide(2);
  load_slide(3);

  slides[0]->visible = true;
}

void key(char k)
{
  if (k == 13 || k == 32) /* enter or space */
  {
    angle = 0;
    scale = 1;

    slides[slidecurrent]->visible = false;
    slidecurrent ++;

    if (slidecurrent == number_of_slides)
        ncknge_quit_no_msg();

    slides[slidecurrent]->visible = true;
    time = 0;
  }
}
void update()
{
   switch (slidecurrent)
   {
     case 0:
     break;

     case 1:

        /* matrix transform animation work around */

         slides[0]->visible = true;
         angle += .3;
         scale *= 1.2;

         if (time > 10)
         {
            slides[0]->visible = false;
            key(13);
         }
     break;
     case 2:
         print(10, 5, BLACK, "Computers r fun");
     break;

     default:
     break;
   }
   transform_set_angle(camera, angle);
   transform_set_scale(camera, scale);
   time ++;
}


int main(int argc, char** argv) {
  chdir(dirname(argv[0]));
  execute(setup, update, key);
  return EXIT_SUCCESS;
}
