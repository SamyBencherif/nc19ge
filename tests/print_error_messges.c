
#include <stdio.h>
#include <errno.h>

void main(void) {
    for (int i=0; i<sys_nerr; i++)
        printf("%d) %s\n", i, sys_errlist[i]);
}
