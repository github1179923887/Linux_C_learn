#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
//信号接收方

static void sig_handler(int sig, siginfo_t *info, void *context)
{
    sigval_t sig_val = info->si_value;
    printf("接收到实时信号： %d\n", sig);
    printf("伴随数据为： %d\n", sig_val.sival_int);
    printf("PID: %d\n", info->si_pid);
    printf("UID: %d\n", info->si_uid);
    exit(0);
}

int main(int argc, char **argv)
{
    struct sigaction sig = {0};
    int num;

    if (argc != 2)  return -1;

    num = atoi(argv[1]);

    //为实时信号绑定信号处理函数
    sig.sa_sigaction = sig_handler;
    sig.sa_flags = SA_SIGINFO; //表示使用结构体中的第二种信号处理函数
    if (sigaction(num, &sig, NULL) == -1)
    {
        perror("sigaction error");
        return -1;
    }

    while (1)
    {
        sleep(1);
    }
    return 0;
}