#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int fd1, fd2;
    int content;
    char buf[1024] = {0};

    fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1)
    {
        printf("open error1\n");
        return -1;
    }

    // fd2 = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, 0744);
    // if (fd2 == -1)
    // {
    //     printf("open error2\n");    //文件已存在也会返回错误
    //     return -1;
    // }
    fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0744);    //此时文件存在会覆盖，第三个 O_ 不同
    if (fd2 == -1)
    {
        printf("open error2\n"); 
        return -1;
    }

    // man 2 lseek
    content = lseek(fd1, 500, SEEK_SET);
    if (content == -1)
    {
        printf("lseek error1\n");
        close(fd1);
        return -1;
    }

    content = read(fd1, buf, 1024);
    if (content == -1)
    {
        printf("read error1\n");
        close(fd1);
        return -1;
    }

    content = write(fd2, buf, 1024);
    if (content == -1)
    {
        printf("write error2\n");
        close(fd2);
        return -1;
    }

    printf("OK!\n");
    close(fd1);
    close(fd2);
    return 0;
}