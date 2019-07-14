
#include <stdlib.h>
#include <stdio.h>

#include "nc19ge.h"

void setup()
{
  NC19GE_GLOBAL_VIEW_MODEL = malloc(1*sizeof(void*));
  NC19GE_GLOBAL_VIEW_MODEL->count = 1;

  quad Q;
  Q.x = 0;
  Q.y = 0;
  Q.w = 2;
  Q.h = 2;
  NC19GE_GLOBAL_VIEW_MODEL->items[0] = &Q;
}

void update()
{
}

int main(int argc, char** argv) {
  execute(setup, update);
  return EXIT_SUCCESS;
}
