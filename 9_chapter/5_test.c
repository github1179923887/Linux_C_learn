#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//子进程会拷贝父进程打开的所有fd，并且共用一个读写指针（接续写）
int main()
{
    int fd;
    fd = open("test.txt", O_WRONLY | O_TRUNC);
    if (fd == -1)
    {
        perror("open error");
        return -1;
    }

    switch(fork())
    {
        case -1:
            perror("fork error");
            close(fd);
            return -1;
        case 0:                             //子进程执行时
            printf("I am child\n");
            write(fd, "Hello World", 11);
            close(fd);
            return 0;
        default:                            //父进程执行时
            printf("I am parent\n");
            write(fd, "12345 67890", 11);
            close(fd);
            return 0;
    }

    close(fd);
    return 0;
}