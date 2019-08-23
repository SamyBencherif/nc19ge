#include <stdlib.h>
#include <stdio.h>

#include "ncknge.h"
#include <math.h>
#ifndef M_PI
  #define M_PI 3.1415926535897
#endif

#include <libgen.h>

component* myBMP;
float ttr;
char* filepath;

void setup()
{
  myBMP = bitmap_from_file(filepath, NULL);
  component_add(myBMP);
  transform_set_scale(camera, 1);

  ttr = 1;
}

void update()
{
  print(0, 0, BLACK, "Use WASD to nudge translation.");
  print(0, 1, BLACK, "Use QE to adjust rotation.");
  print(0, 2, BLACK, "Use RF to set scale.");

  print(0, 4, BLACK, "COLORS 0      1 2 3 4 5 6 7 \' \'");
  print(0, 5, BLACK, "      (BLACK)               (CLEAR)");
  print(14, 5, RED, " ");
  print(16, 5, GREEN, " ");
  print(18, 5, YELLOW, " ");
  print(20, 5, BLUE, " ");
  print(22, 5, MAGENTA, " ");
  print(24, 5, CYAN, " ");
  print(26, 5, WHITE, " ");

  ttr -= 1;

  if (ttr <= 0)
  {
    bitmap_from_file(filepath, myBMP);
    ttr = 1;
  }
}

void key(char k)
{
  if (k == 'w') {
    transform_displace(camera, 0, 1);
  }
  if (k == 's') {
    transform_displace(camera, 0, -1);
  }
  if (k == 'a') {
    transform_displace(camera, -1, 0);
  }
  if (k == 'd') {
    transform_displace(camera, 1, 0);
  }
  if (k == 'q') {
    transform_set_angle(camera, camera->angle + M_PI/12);
  }
  if (k == 'e') {
    transform_set_angle(camera, camera->angle - M_PI/12);
  }
  if (k == 'r') {
    transform_set_scale(camera, camera->scale/1.1);
  }
  if (k == 'f') {
    transform_set_scale(camera, camera->scale*1.1);
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
