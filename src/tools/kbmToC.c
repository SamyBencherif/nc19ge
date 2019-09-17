
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
    if (argc != 5)
    {
        printf("Bad argument count.\n");
        printf("Usage: ./kbmToC -d src/tex -o bin/resources\n");
    }

    if (argv[1] != "-d")
    {
        printf("%s\n", argv[1]);
        printf("^ Unexpected flag at position 1.\n");
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
