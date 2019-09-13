#include <stdio.h>

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
        printf("^ Unexpected flag at position 1.\n")
    }
}
