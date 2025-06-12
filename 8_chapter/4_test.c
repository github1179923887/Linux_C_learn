#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
//raise(sig) = kill(getpid(), sig)
static void sig_handler(int sig)
{
    printf("Received signal: %d\n", sig);
}

int main(int argc, char **argv)
{
    if (argc > 2)   return 1;
    struct sigaction sig = {0};
    int ret = 0;
    
    sig.sa_handler = sig_handler;
    sig.sa_flags = 0;
    ret = sigaction(SIGINT, &sig, NULL);
    if (ret == -1)
    {
        perror("sigaction error");
        return -1;
    }
    
    while (1)
    {
        if (raise(SIGINT) != 0)
        {
            printf("raise error\n");
            return -1;
        }
        sleep(3);
    }

    return 0;
}