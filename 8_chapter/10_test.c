#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
//raise(sig) = kill(getpid(), sig)
static void sig_handler(int sig)
{
    printf("接收到信号：%d\n", sig);
}

int main(int argc, char **argv)
{
    struct sigaction sig = {0};
    sigset_t sig_set;

    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGABRT);
    //加入信号掩码
    if (sigprocmask(SIG_BLOCK, &sig_set, NULL) == -1)
        return -1;

    //sig.sa_handler = sig_handler; //绑定信号处理函数
    sig.sa_handler = SIG_IGN; //忽略信号
    sig.sa_flags = 0;
    if (sigaction(SIGABRT, &sig, NULL) == -1)
    {
        perror("sigaction error");
        return -1;
    }

    sleep(2);
    abort();

    while (1)
    {
        sleep(1);
    }

    return 0;
}