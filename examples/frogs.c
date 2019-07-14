
#include <stdlib.h>
#include <stdio.h>

#include "nc19ge.h"

void setup()
{
}

void update()
{
  quad(0,0,1,1);
}

int main(int argc, char** argv) {
  execute(setup, update);
  return EXIT_SUCCESS;
}
