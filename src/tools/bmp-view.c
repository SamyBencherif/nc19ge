#include <stdlib.h>
#include <stdio.h>

#include "ncknge.h"
#include "ncurses.h"
#include <math.h>
#ifndef M_PI
    #define M_PI 3.1415926535897
#endif

#include <libgen.h>

component* myBMP;
char* filepath;

void setup()
{
    myBMP = bitmap_from_file(filepath, NULL);
    component_add(myBMP);
    transform_set_scale(camera, 1);
    mousemask(1, 0);
    NCKNGE_AUTO_REDRAW(0);
}

void update()
{
    print(0, 0, BLACK, "COLORS 0      1 2 3 4 5 6 7 \' \'");
    print(0, 1, BLACK, "      (BLACK)                (CLEAR)");
    print(14, 1, RED, " ");
    print(16, 1, GREEN, " ");
    print(18, 1, YELLOW, " ");
    print(20, 1, BLUE, " ");
    print(22, 1, MAGENTA, " ");
    print(24, 1, CYAN, " ");
    print(26, 1, WHITE, " ");

    bitmap_from_file(filepath, myBMP);
}

void key(char k)
{
    if (k == -103)
    {
        MEVENT* mev = malloc(sizeof(MEVENT));
        int status = getmouse(mev);
        if (status == OK)
        {
            print(mev->x, mev->y, BLUE, "4");
        }
        else
        {
            perror("getmouse");
        }
    }
}

int main(int argc, char** argv) {

    if (argc < 2)
    {
        ncknge_error("Usage: %s file.kbm\n", basename(argv[0]));
    }

    filepath = argv[1];

    execute(setup, update, key);
    return EXIT_SUCCESS;
}
