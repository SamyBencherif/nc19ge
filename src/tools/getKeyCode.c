#include "ncknge.h"

void setup()
{
}

void update()
{
}

void key(char k)
{
  ncknge_error("You pressed <k:%d>!\n", (int)k);
}

int main(void)
{
  execute(setup, update, key);
}
