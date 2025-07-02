//!互斥锁：初始化、加锁解锁、非阻塞加锁、销毁、死锁
//第一种线程同步方法，用于解决数据不一致问题
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

//!共享资源，静态全局变量
static int g_count = 0;
//!互斥锁对象，静态全局变量
static pthread_mutex_t mutex;

static void *new_thread_start(void *arg)
{
    int loops = *((int*)arg);
    int l_count, j;

    //!创造并发访问情况
    for (j = 0; j < loops; j++)
    {
        //!互斥锁上锁
        //pthread_mutex_lock(&mutex);
        //!非阻塞方式上锁，上锁成功才会跳出while
        while(pthread_mutex_trylock(&mutex));

        l_count = g_count;
        l_count++;
        g_count = l_count;

        //!互斥锁解锁
        pthread_mutex_unlock(&mutex);
    }
    
    return (void*)0;
}

static int loops;

int main(int argc, char *argv[])
{
    pthread_t tid1, tid2;
    int ret;

    if (argc != 2)  loops = 10000000;
    else    loops = atoi(argv[1]);

    //!初始化互斥锁，第一个参数为互斥锁对象，第二个参数表示默认互斥锁属性
    pthread_mutex_init(&mutex, NULL);

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

    //!销毁互斥锁，在进程退出之前。销毁后需要对互斥锁对象重新初始化才可以上锁解锁
    pthread_mutex_destroy(&mutex);
    exit(0);
}

//!死锁：某线程 1 占用一个互斥锁的同时想对另一个互斥锁执行上锁操作但被阻塞，而另一个互斥锁占有者 2 对1的互斥锁执行上锁操作被阻塞，这就会导致死锁