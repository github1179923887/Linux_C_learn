#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void bye1()
{
    printf("bye 1\n");
}

static void bye2()
{
    printf("bye 2\n");
}

static void bye3()
{
    printf("bye 3\n");
}

int main()
{
    //绑定终止处理函数
    atexit(bye1);   // 参数本该是一个指针，但是函数名可以被隐性的转化为函数指针，所以不需要加地址符&
    atexit(bye2);
    atexit(bye3);
    //可绑定多个并且都会执行，但执行顺序与绑定顺序相反

    printf("Hello gfd!\n");
    //终止函数，0表示正常终止，非0表示发生错误的终止（如open错误），就像return
    exit(0);   // 而"_exit(0)" 不会绑定终止处理函数，也不会刷新stdio缓冲

    //return是c语言的语句，但是也可以以相同的方法绑定到终止处理函数，也会刷新stdio缓冲
    return 0;

    //abort是异常终止函数，不会绑定终止处理函数，也不会刷新stdio缓冲
    abort();
}