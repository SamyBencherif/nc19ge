
/* LIB */

#include <stdlib.h>
#include <string.h>
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

int cursor_x = 0;
int cursor_y = 0;


/* HELPER FUNCTIONS */

int clampi(int low, int x, int high)
{
    if (x < low)
        return low;
    if (x > high)
        return high;
    return x;
}

/* print 1-line of centered text */
void printc(int x, int y, color c, char* msg)
{
    print(x - strlen(msg)/2, y, c, msg);
}

/* print multiple left justified lines of text */
void printb(int x, int y, color c, char* msg)
{
    int xd = 0;
    int yd = 0;
    int i;
    for (i = 0; i < strlen(msg); i ++)
    {
        if (msg[i] == '\n')
        {
            xd = 0;
            yd ++;
        }
        else
        {
            char toPrint[3];

            toPrint[0] = msg[i];
            toPrint[1] = '\0';

            if (msg[i] == '%') /* special case to support % symbol */
            {
                toPrint[1] = '%';
                toPrint[2] = '\0';
            }

            print(x + xd, y + yd, c, toPrint);
            xd ++;
        }
    }
}

/* called before each scene */
void init()
{
    cursor_x = 0;
    cursor_y = 0;
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

        printc(W/2, H/2 + 6, BLACK, "~ Press Any Key To Begin ~");

        if (t%5 == 0)
        {
            title_img_0->visible = !title_img_0->visible;
            title_img_1->visible = !title_img_1->visible;
        }

        break;
        case identity:
        /* printc(W/2, H/2-8, BLACK, "First, choose your identity."); */
        /* printc(W/2, H/2-6, BLACK, "What is your skill?"); */

        printb(5, 5, BLACK, 
            "First, choose your identity.\n"
            "\n"
            "What is your skill?\n"
            "\n"
        );

        cursor_y = clampi(0, cursor_y, 4);

        print(5, 9 + cursor_y, CYAN, "I am ");

        print(10, 9, CYAN*(cursor_y == 0), "Friendly");

        if (cursor_y == 0)
            printb(60, 5, BLACK, 
            "Friendliness Trait\n"
            "---------------------------------------\n"
            "\n"
            "* You will have special options \n"
            "  available to you during negotiations.\n"
            "\n"
            "* Other characters will be trusting of\n"
            "  you.\n"
            );


        print(10, 10, CYAN*(cursor_y == 1), "Swift");
        
        if (cursor_y == 1)
            printb(60, 5, BLACK, 
            "Swiftness Trait\n"
            "---------------------------------------\n"
            "\n"
            "* Evasion maneuvers are 23% more likely\n"
            "  to be successful.\n"
            "\n"
            "* Sneaky maneuvers are 30% more likely\n"
            "  to be successful.\n"
            "\n"
            "* Combat strength is increased 5%."
            );

        print(10, 11, CYAN*(cursor_y == 2), "Frugal");

        if (cursor_y == 2)
            printb(60, 5, BLACK, 
            "Frugality Trait\n"
            "---------------------------------------\n"
            "\n"
            "* You always get the best bargain\n"
            "\n"
            "* You are trusted with money.\n"
            "\n"
            "* Looting yield increased 12%."
            );

        print(10, 12, CYAN*(cursor_y == 3), "Courageous");

        if (cursor_y == 3)
            printb(60, 5, BLACK, 
            "Courage Trait\n"
            "---------------------------------------\n"
            "\n"
            "* Combat strength increased 50%.\n"
            "\n"
            "* You can collect weapons from defeated\n"
            "  enemies.\n"
            );

        print(10, 13, CYAN*(cursor_y == 4), "Enchanting");

        if (cursor_y == 4)
            printb(60, 5, BLACK, 
            "Enchanter Trait\n"
            "---------------------------------------\n"
            "* You ae unsure of your capabilities.\n"
            );

        print(5, 15, BLACK, "Use UP / DOWN to select. ENTER to choose.");

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

    if (k == 2) /* Down */
        cursor_y ++;
    if (k == 3) /* Up */
        cursor_y --;
    if (k == 4) /* Left */
        cursor_x --;
    if (k == 5) /* Right */
        cursor_x ++; 
}

int main(int argc, char** argv) {
  execute(setup, update, key);
  return EXIT_SUCCESS;
}
