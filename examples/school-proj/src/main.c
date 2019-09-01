#include <stdlib.h>
#include <stdio.h>

#include "ncknge.h"

#include <math.h>
#ifndef M_PI
  #define M_PI 3.1415926535897
#endif

#define number_of_slides 6

/* list all included sldes */
#include "resource/KBM_SLIDE1.c"
#include "resource/KBM_SLIDE2.c"
#include "resource/KBM_SLIDE3.c"
#include "resource/KBM_SLIDE4.c"

#include "resource/KBM_BLANK.c"

#define load_slide(n) {\
  slides[n-1] = bitmap_create(KBM_SLIDE##n##_W, KBM_SLIDE##n##_H, KBM_SLIDE##n); \
  slides[n-1]->transform->translate->x = -KBM_SLIDE##n##_W/2; \
  slides[n-1]->transform->translate->y = -KBM_SLIDE##n##_H/2*BLOCK_ASPECT; \
  slides[n-1]->visible = false; \
  component_add(slides[n-1]); \
}

#define load_blank(n) {\
  slides[n-1] = bitmap_create(KBM_BLANK_W, KBM_BLANK_H, KBM_BLANK); \
  slides[n-1]->transform->translate->x = -KBM_BLANK_W/2; \
  slides[n-1]->transform->translate->y = -KBM_BLANK_H/2*BLOCK_ASPECT; \
  slides[n-1]->visible = false; \
  component_add(slides[n-1]); \
}

component* slides[number_of_slides];

int slidecurrent;
int time;

float angle;
float scale;


enum {DUDE_ARM_L, DUDE_ARM_R, DUDE_TORSO, DUDE_HEAD, DUDE_LEG_L, DUDE_LEG_R};
component* dude[6];

void setup()
{
  slidecurrent = 0;
  time = 0;

  angle = 0;
  scale = 1;

  /* this is a macro, cannot be put in loop
     should load all slides from `number_of_slides` */
  load_slide(1);
  load_blank(2);
  load_slide(3);
  load_slide(4);
  load_blank(5);
  load_blank(6);

  slides[0]->visible = true;

  /*
   * The creation of man:
   */
  dude[DUDE_HEAD] = ellipse_new(0, 0, 7., 9., YELLOW);
  dude[DUDE_ARM_L] = quad_new(-3, -9, 6, 18, BLUE);
  dude[DUDE_ARM_R] = quad_new(-3, -9, 6, 18, BLUE);
  dude[DUDE_TORSO] = quad_new(-8, -11, 17, 23, RED);
  dude[DUDE_LEG_L] = quad_new(-5, -10, 10, 20, BLUE);
  dude[DUDE_LEG_R] = quad_new(-5, -10, 10, 20, BLUE);
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

    if (slidecurrent > 1) /* special case */
    {
      slides[0]->visible = false;
    }

    if (slidecurrent == 5) /* special case */
    {
      component_add(dude[DUDE_HEAD]);
      dude[DUDE_HEAD]->transform->translate->y = 23;

      component_add(dude[DUDE_ARM_L]);

      component_add(dude[DUDE_LEG_L]);
      dude[DUDE_LEG_L]->transform->translate->y = -20;

      component_add(dude[DUDE_TORSO]);

      component_add(dude[DUDE_ARM_R]);

      component_add(dude[DUDE_LEG_R]);
      dude[DUDE_LEG_R]->transform->translate->y = -20;
    }

    slides[slidecurrent]->visible = true;
    time = 0;
  }
}
void update()
{
   switch (slidecurrent + 1)
   {
     case 1:
     break;

     case 2:

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
     case 3:
         print(10, 5, BLACK, "Today we will be educating you silly children about compyooters.");
         print(W-90, H-10, BLACK, "Did you know they were invented by a monkey in a russian man's basement?");
     break;
     case 4:
         print(10, 5, BLACK, "The first computers were made for the noble");
         print(10, 6, BLACK, "goal of flinging giant flaming rocks into");
         print(10, 7, BLACK, "space.");
     break;
     case 5:
         print(W/2-5, H/2, BLACK, "~ The End ~");
     case 6:
         transform_set_angle(dude[DUDE_ARM_L]->transform, sin(-3*time/6.));
         dude[DUDE_ARM_L]->transform->translate->x = 10*sin(-3*time/6.);

         transform_set_angle(dude[DUDE_ARM_R]->transform, sin(3*time/6.));
         dude[DUDE_ARM_R]->transform->translate->x = 10*sin(3*time/6.);

         transform_set_angle(dude[DUDE_LEG_L]->transform, sin(-3*time/10.));
         dude[DUDE_LEG_L]->transform->translate->x = 10*sin(-3*time/10.);

         transform_set_angle(dude[DUDE_LEG_R]->transform, sin(3*time/10.));
         dude[DUDE_LEG_R]->transform->translate->x = 10*sin(3*time/10.);

         dude[DUDE_HEAD]->transform->translate->y = 23 + 2 * sin (time);

         camera->translate-> y = sin(time);

     default:
     break;
   }
   transform_set_angle(camera, angle);
   transform_set_scale(camera, scale);
   time ++;
}


int main(int argc, char** argv) {
  execute(setup, update, key);
  return EXIT_SUCCESS;
}
