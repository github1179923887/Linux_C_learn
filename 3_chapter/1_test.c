#include <stdio.h>
#include <errno.h> // 包含全局变量errno，大部分函数在发生错误时会改变其值
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    /* 打开文件 */
    fd = open("./test_file", O_RDONLY);
    if (-1 == fd)
    {
        printf("Error: %s\n", strerror(errno));     // strerror 根据errno的值返回具体的错误信息
        perror("");     // 自动根据errno值打印具体的错误信息，双引号内的字符串会在错误信息前显示，可用来注释
        perror("open error");
        return -1;
    }
    close(fd);
    return 0;
}