#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
//信号发送方
int main(int argc, char **argv)
{
    union sigval sig_val;   // 伴随数据体
    int pid;
    int sig;

    if (argc != 3)  return -1;
    
    pid = atoi(argv[1]);
    sig = atoi(argv[2]);
    printf("pid: %d ; signal: %d\n", pid, sig);

    //发送信号
    sig_val.sival_int = 10; // 伴随数据
    if (sigqueue(pid, sig, sig_val) == -1)
    {
        perror("sigqueue error");
        return -1;
    }
    puts("信号发送成功");

    return 0;
}