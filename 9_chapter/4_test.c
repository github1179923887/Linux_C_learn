#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int ret;
    ret = fork();     
    //调用一次会产生两个返回值，等同于复制父进程给子进程（几乎完全），两进程数据、堆栈、进程空间等是独立的
    //子进程只会执行fork之后的代码段
    if (ret == -1)
    {
        perror("fork error");
        return -1;
    }
    else if (ret == 0)  //子进程执行时
    {
        printf("I am child of PPID: %d, my PID: %d\n", getppid(), getpid());
    }
    else    //父进程执行时
    {
        printf("I am parent of PID: %d, my CPID: %d\n", getpid(), ret);
    }

    // printf("Hello World!\n");   //此时该语句会执行两次，父进程一次，子进程一次
    // printf("%d\n", ret);    //第一次是父进程的返回值(>0，实际上就是子进程的PID)，第二次是子进程的返回值并且子进程返回值=0
    return 0;
}