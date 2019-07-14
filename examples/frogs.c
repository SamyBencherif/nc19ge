
#include <stdlib.h>
#include <stdio.h>

#include "nc19ge.h"

void setup()
{
  NC19GE_GLOBAL_VIEW_MODEL = malloc(sizeof(NC19GE_GLOBAL_VIEW_MODEL));
  NC19GE_GLOBAL_VIEW_MODEL->items = malloc(1*sizeof(void*));
  NC19GE_GLOBAL_VIEW_MODEL->count = 1;

  quad* Q = malloc(sizeof(quad));
  Q->x = 0;
  Q->y = 0;
  Q->w = 4;
  Q->h = 4;
  NC19GE_GLOBAL_VIEW_MODEL->items[0] = Q;
}

void update()
{
}

int main(int argc, char** argv) {
  execute(setup, update);
  return EXIT_SUCCESS;
}
