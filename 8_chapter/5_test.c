#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
//raise(sig) = kill(getpid(), sig)
static void sig_handler(int sig)
{
    printf("Alarm timeout\n");
    //return;没用
    exit(0);
}

int main(int argc, char **argv)
{
    if (argc != 2)   return -1;
    struct sigaction sig = {0};
    int second = 0, ret = 0;
    
    sig.sa_handler = sig_handler;
    sig.sa_flags = 0;
    ret = sigaction(SIGALRM, &sig, NULL);
    if (ret == -1)
    {
        perror("sigaction error");
        return -1;
    }

    second = atoi(argv[1]);
    printf("定时时长：%d 秒\n", second);
    alarm(second);
    
    while (1)
    {
        sleep(1);
    }

    return 0;
}