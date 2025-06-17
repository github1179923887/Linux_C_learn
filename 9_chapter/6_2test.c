#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char *argv[])
{
    char **ep = NULL;

    for (int j = 0; j < argc; j++)
    {
        printf("argv[%d]: %s\n", j, argv[j]);
    }

    puts("env: ");

    for (ep = environ; *ep != NULL; ep++)
    {
        printf("%s\n", *ep);
    }

    return 0;
}