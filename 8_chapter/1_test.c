#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void sig_handler(int sig)
{
    printf("Received signal: %d\n", sig);
}

int main()
{
    sig_t ret = NULL;
    ret = signal(SIGINT, (sig_t)sig_handler);
    if (SIG_ERR == ret)
    {
        perror("signal error");
        return -1;
    }
    while (1)
    {
        sleep(1);
    }

    return 0;
}