#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;
    int ret;

    // 在终端使用man 2 open命令查看open函数所需头文件
    fd = open("./test.txt", O_WRONLY | O_CREAT | O_EXCL, 0644);
    // O_WRONLY | O_CREAT | O_EXCL，创建文件常用组合，0（8进制）644指U（用户）、G（组成员）、O（其他）的权限
    if (fd == -1)
    {
        // 在终端使用man 3 print命令查看print函数所需头文件，因为print是库函数
        printf("open error\n");
        return -1;
    }

    printf("open ok!\n");

    // 在终端使用man 2 write命令查看write函数所需头文件，与close相同
    ret = write(fd, "Hello World", 11); // 11指字节数
    if (ret == -1)
    {
        printf("write error\n");
        close(fd);
        return -1;
    }

    printf("write %d bytes ok!\n", ret);
    close(fd);

    return 0;
}