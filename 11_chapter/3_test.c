//! 条件变量：定义、初始化、发送信号、接收信号
// 第二种线程同步方法，用于解决数据不一致问题，一般与互斥锁配合使用
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

//! 共享资源，静态全局变量
static int g_avail = 0;
//! 互斥锁对象，静态全局变量
static pthread_mutex_t mutex;
//! 条件变量对象
static pthread_cond_t cond;

// 消费者线程
static void *consumer_thread(void *arg)
{
    for (;;)
    {
        pthread_mutex_lock(&mutex);

        //!必须使用while，因为若有多个消费者且产品被其他人先购买了，那么就不满足条件，因此wait返回后需要马上判断条件
        while (g_avail <= 0)
            pthread_cond_wait(&cond, &mutex);   //!等待条件满足

        while (g_avail > 0)
        {
            g_avail--;  //消费者购买产品
            printf("购买\n");
        }
            

        pthread_mutex_unlock(&mutex);
    }

    return (void *)0;
}

//生产者
int main(int argc, char *argv[])
{
    pthread_t tid;
    int ret;

    //! 初始化互斥锁，第一个参数为互斥锁对象，第二个参数表示默认互斥锁属性
    pthread_mutex_init(&mutex, NULL);
    //! 初始化条件变量
    pthread_cond_init(&cond, NULL);

    //! 创建线程
    ret = pthread_create(&tid, NULL, consumer_thread, NULL);
    if (ret)
    {
        fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
        exit(-1);
    }

    for (;;)
    {
        pthread_mutex_lock(&mutex);
        g_avail++;  //生产产品
        printf("生产\n");
        pthread_mutex_unlock(&mutex);
        //!向条件变量发送信号
        pthread_cond_signal(&cond);
        sleep(1);
    }

    ret = pthread_join(tid, NULL);
    if (ret)
    {
        fprintf(stderr, "pthread_join error: %s\n", strerror(ret));
    }

    //! 销毁互斥锁，在进程退出之前。销毁后需要对互斥锁对象重新初始化才可以上锁解锁
    pthread_mutex_destroy(&mutex);
    //! 销毁条件变量
    pthread_cond_destroy(&cond);
    exit(0);
}