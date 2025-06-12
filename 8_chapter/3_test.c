#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char **argv)
{
    if (argc > 2)   return 1;
    
    int pid;
    pid = atoi(argv[1]);    //将传入的字符串转化为整型
    printf("pid: %d\n", pid);

    // 向pid制定的进程发送信号
    if (kill(pid, SIGINT) == -1)
    {
        perror("kill error");
        return -1;
    }

    return 0;
}