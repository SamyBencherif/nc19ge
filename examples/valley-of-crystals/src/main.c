
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
#include "resource/KBM_GIFT_GUN.c"
component* title_img_0;
component* title_img_1;
component* gift_gun;

/* SCENES */

typedef enum {title, identity, gift} scene;
scene present;

/* DATA */

int t = 0;

int cursor_x = 0;
int cursor_y = 0;

typedef enum {unchoosen, friendly, swift, frugal, courageous, enchanting, wise} skill;
skill player_skill = unchoosen;

/* CHEAT CODES */

int cheat_index = 0;
char* cheat_sequence_wisdom = "ppp[*";

bool cheat_wisdom_active = false;

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
        /* TODO move to unloader fn */
        break;
        case gift:
        cursor_y = 0;
        gift_gun = bitmap_create(KBM_GIFT_GUN_W,
                KBM_GIFT_GUN_H,
                KBM_GIFT_GUN);
        gift_gun->transform->translate->x = -KBM_GIFT_GUN_W/2;
        gift_gun->transform->translate->y = (-KBM_GIFT_GUN_H/2
                                                  + 2) * BLOCK_ASPECT;
        component_add(gift_gun);
        break;
        default:
        break;
    }
}

#ifdef dev
int value_tester;

void dev_init()
{
  /* initialize development variables */
  value_tester = 0;

  /* skip ahead to the part we are working on */
  present = gift;
  init();

  /* set any important state variables */
  /* ... */
}
#endif

void setup()
{
    present = title;
    #ifdef dev
    dev_init();
    #else
    init();
    #endif
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

        print(2, 3, BLACK, "First, choose your identity.");

        print(5, 5, BLACK, "What is your skill?");

        cursor_y = clampi(0, cursor_y, 4);

        int trait_info_x = 37;
        int trait_info_y = 5;


        if (cheat_wisdom_active)
        {
            /* Notice the large amount of space after 'am', produces a blue bar.*/
            print(5, 9 + cursor_y, CYAN, "I am                       ");

            /* ENTER is not in caps here */
            print(5, 20, BLACK, "Use UP / DOWN to select. enter to choose.");
        }
        else
        {
            print(5, 9 + cursor_y, CYAN, "I am ");

            print(10, 9, CYAN*(cursor_y == 0), "Friendly");

            if (cursor_y == 0)
                printb(trait_info_x, trait_info_y, BLACK,
                "Friendliness Trait\n"
                "---------------------------------------\n"
                "\n"
                "* You are trustworthy and relatable.\n"
                "\n"
                "* You will have special options \n"
                "  available to you during negotiations.\n"
                );


            print(10, 10, CYAN*(cursor_y == 1), "Swift");

            if (cursor_y == 1)
                printb(trait_info_x, trait_info_y, BLACK,
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
                printb(trait_info_x, trait_info_y, BLACK,
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
                printb(trait_info_x, trait_info_y, BLACK,
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
                printb(trait_info_x, trait_info_y, BLACK,
                "Enchanter Trait\n"
                "---------------------------------------\n"
                "\n"
                "* You are unsure of your capabilities.\n"
                );

            print(5, 20, BLACK, "Use UP / DOWN to select. ENTER to choose.");
        }


        break;
        case gift:

        cursor_y = clampi(0, cursor_y, 0);

        print(2, 3, BLACK, "Now, choose your gift.");
        print(5, 5 + cursor_y, CYAN, "I choose ");
        print(14, 5, CYAN*(cursor_y == 0), "the gun.");

        break;
        default:
        break;
    }
    t++;

    #ifdef dev

    /* DEBUG info */
    print(
        0, 0, BLACK,
        "value tester: %d "
        "screen: %dx%d "
        "cursor: %d,%d",
        value_tester,
        W, H,
        cursor_x, cursor_y
    );

    #endif
}

void key(char k)
{
    #ifdef dev
    if ( k == '[')
    {
       value_tester -= 1;
       return;
    }
    if ( k == ']')
    {
       value_tester += 1;
       return;
    }
    #endif
    switch (present)
    {
        case title:

        if ( k == cheat_sequence_wisdom[cheat_index] )
        {
            cheat_index ++;
            if (cheat_index < 5)
                return;

            /* cheat code successful */
            cheat_wisdom_active = true;
            cheat_index = 0;

        } else
        {
            cheat_index = 0;
        }

        present = identity;
        init();
        break;
        case identity:
        if (k == 13) /* RETURN key */
        {
            if (cursor_y == 0)
                player_skill = friendly;
            if (cursor_y == 1)
                player_skill = swift;
            if (cursor_y == 2)
                player_skill = frugal;

            if (cheat_wisdom_active)
                player_skill = wise;

            present = gift;
            init();
        }
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
