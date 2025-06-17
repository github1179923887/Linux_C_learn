#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//system函数内部使用fork（父）,excle族（子）以及waitpid（父）函数实现了调用shell命令的功能
//返回值及简化运作方式见7_test.doc

int main()
{
    int ret = -1;

    ret = system("ls -al");
    if (ret == -1)
    {
        perror("system error");
        return -1;
    }

    //检验子进程是否正常终止
    printf("status: %d\n", WIFEXITED(ret));

    return 0;
}
