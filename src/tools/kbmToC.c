
#define _DEFAULT_SOURCE
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

int main(int argc, char** argv)
{
    if (argc != 5)
    {
        fprintf(stderr, "Bad argument count.\n");
        fprintf(stderr, 
                "Usage: ./kbmToC -d src/tex -o bin/resources\n");
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "-d") != 0)
    {
        fprintf(stderr, "%s\n", argv[1]);
        fprintf(stderr, "^ Unexpected flag at position 1.\n");
        exit(EXIT_FAILURE);
    }

    struct dirent **namelist;
    int n;

    n = scandir("tex", &namelist, NULL, alphasort);
    if (n == -1) {
        perror("scandir");
        exit(EXIT_FAILURE);
    }

    while (n--) {

        printf("%s\n", namelist[n]->d_name);
        free(namelist[n]);
    }

    free(namelist);

    exit(EXIT_SUCCESS);

}
