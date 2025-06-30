//!获取线程ID，创建、终止、回收线程
//!编译时需要指定链接库pthread，命令：gcc -o xx xx.c -lpthread，现在不需要了
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

//!新线程绑定函数
static void *new_thread_start(void *arg)
{
    printf("新线程开始\n");
    //!获取自身线程ID，linux下该值为 unsigned long int 型，其他系统下不一定，因此正常情况下需要视作未知数据类型，此处是示范
    printf("新线程ID：%lu\n", pthread_self());
    sleep(2);
    printf("新线程结束\n");
    //!终止线程，任意线程若调用exit之类的函数，会直接导致整个进程终止！！！
    //也可以使用return (void*)x
    pthread_exit((void*)10);   //可在任意处调用，不必在最后，必须要强制转化为(void*)型或者NULL
}

int main()
{
    pthread_t tid;
    void *tret;
    int ret;

    //!创建线程，第一个参数用于保存新线程ID；第二个参数可定义线程属性，NULL表示默认；第四个参数一般需要指向一个全局或堆变量，确保线程终止前该对象存在，NULL表示不需要参数
    //!第三个指向新线程开始运行的函数，该函数参数即为第四个参数，若需要多个参数，则需要定义一个结构体并将结构体地址赋予第四个参数
    ret = pthread_create(&tid, NULL, new_thread_start, NULL);
    if (ret)
    {
        fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
        exit(-1);
    }

    //!回收线程(只能阻塞等待)，第二个参数不为NULL时，存储目标线程的退出状态(返回值)，若目标被pthread_cancel取消，则需将PTHREAD_CANCELED放在其中
    //进程中任意线程均可以等待其他任意线程的终止
    ret = pthread_join(tid, &tret);
    if (ret)
    {
        fprintf(stderr, "pthread_join error: %s\n", strerror(ret));
        exit(-1);
    }

    printf("新线程终止并回收，code=%ld\n", (long)tret);

    exit(0);
}