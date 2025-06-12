#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

static void sig_handler(int sig)
{
    printf("执行信号处理函数...\n");
    exit(0);
}

int main()
{
    struct sigaction sig = {0};
    sigset_t sig_set;
    int second = 0, ret = 0;
    
    sig.sa_handler = sig_handler;
    sig.sa_flags = 0;
    ret = sigaction(SIGINT, &sig, NULL);
    if (ret == -1)
    {
        perror("sigaction error");
        return -1;
    }

    // 信号集初始化
    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGINT);    // 将SIGINT信号加入信号集

    // SIG_BLOCK：向信号掩码中添加信号；SIG_UNBLOCK：向信号掩码中删去信号；SIG_SETMASK：向信号掩码中替换信号集；NULL表示不保留旧信号掩码
    if (sigprocmask(SIG_BLOCK, &sig_set, NULL) == -1)   return -1;

    raise(SIGINT);  // 此时进程接收不到该信号

    sleep(2);
    printf("休眠结束\n");

    if (sigprocmask(SIG_UNBLOCK, &sig_set, NULL) == -1)   
    {
        printf("sigprocmask error\n");
        return -1;
    }

    raise(SIGINT);  // 此时进程接收到该信号，执行信号处理函数

    return 0;
}