//!取消线程，取消性状态和类型设置，取消点（某些函数），创建取消点
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

// static void *new_thread_start(void *arg)
// {
//     //!设置为不可被取消状态，可取消状态（即默认状态）是:PTHREAD_CANCEL_ENABLE
//     pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

//     printf("新线程开始\n");
//     for (;;)
//     {
//         printf("新线程--running\n");
//         sleep(2);
//     }
//     return (void*)0;
// }

static void *new_thread_start(void *arg)
{
    //printf("新线程开始\n");   //!printf在此也是取消点
    for (;;)
    {
        //!创建一个取消点，没有该语句的话该线程不会因为接收到取消请求而取消，因为没有取消点
        pthread_testcancel();
    }
    return (void*)0;
}

int main()
{
    pthread_t tid;
    void *tret;
    int ret;

    ret = pthread_create(&tid, NULL, new_thread_start, NULL);
    if (ret)
    {
        fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
        exit(-1);
    }

    //!发生取消线程请求
    ret = pthread_cancel(tid);
    if (ret)
    {
        fprintf(stderr, "pthread_cancel error: %s\n", strerror(ret));
        exit(-1);
    }
    //!另有pthread_setcanceltype(tid)函数用与设置类型，但极少用到非默认类型(即PTHREAD_CANCEL_ASYNCHRONOUS)，表示会在任何时间点取消进程
    //!默认状态为PTHREAD_CANCEL_DEFERRED，表示接收到取消请求后先挂起请求，知道线程到达某个取消点时取消进程

    ret = pthread_join(tid, &tret);
    if (ret)
    {
        fprintf(stderr, "pthread_join error: %s\n", strerror(ret));
        exit(-1);
    }

    printf("新线程终止并回收，code=%ld\n", (long)tret);

    exit(0);
}