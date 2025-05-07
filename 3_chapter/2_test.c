// 创建空洞文件，可用于多线程同时写入数据

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static unsigned char buf[4096];

int main()
{
    int fd;
    int ret;

    fd = open("./test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0744);
    if (fd == -1)
    {
        perror("open error");
        return -1;
    }

    ret = lseek(fd, 4096, SEEK_SET);
    if (ret == -1)
    {
        perror("lseek error");
        close(fd);
        return -1;
    }

    ret = write(fd, buf, 4096);
    if (ret == -1)
    {
        perror("write error");
        close(fd);
        return -1;
    }

    printf("write %d bytes\n", ret);

    close(fd);

    return 0;
}