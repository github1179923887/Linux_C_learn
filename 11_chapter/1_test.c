//!测试因多线程并发访问共享资源导致的数据不一致现象
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

//!共享资源，静态全局变量
static int g_count = 0;

static void *new_thread_start(void *arg)
{
    int loops = *((int*)arg);
    int l_count, j;

    //!创造并发访问情况
    for (j = 0; j < loops; j++)
    {
        l_count = g_count;
        l_count++;
        g_count = l_count;
    }
    
    return (void*)0;
}

static int loops;

int main(int argc, char *argv[])
{
    pthread_t tid1, tid2;
    int ret;

    if (argc != 2)  loops = 10000000;   //!结果理论上为20000000，但实际不是，这就是数据不一致现象
    else    loops = atoi(argv[1]);

    //!创建多线程环境
    ret = pthread_create(&tid1, NULL, new_thread_start, &loops);
    if (ret)
    {
        fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
        exit(-1);
    }
    ret = pthread_create(&tid2, NULL, new_thread_start, &loops);
    if (ret)
    {
        fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
        exit(-1);
    }

    sleep(1);

    ret = pthread_join(tid1, NULL);
    if (ret)
    {
        fprintf(stderr, "pthread_join error: %s\n", strerror(ret));
    }
    ret = pthread_join(tid2, NULL);
    if (ret)
    {
        fprintf(stderr, "pthread_join error: %s\n", strerror(ret));
    }

    printf("g_count=%d\n", g_count);

    exit(0);
}