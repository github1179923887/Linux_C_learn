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
    //ret = signal(SIGINT, SIG_IGN);忽略信号，注意SIGKILL和SIGSTOP不会忽略，就会报错
    //ret = signal(SIGINT, SIG_DFL);默认处理
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