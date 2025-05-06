#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;
    char buf[125] = {0};
    int ret;

    fd = open("./test.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("open error\n");
        return -1;
    }

    printf("open ok!\n");

    ret = read(fd, buf, 11);
    if (ret == -1)
    {
        printf("read error\n");
        close(fd);
        return -1;
    }

    printf("read %d bytes: %s\n", ret, buf);
    close(fd);

    return 0;
}