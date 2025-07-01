//!分离线程
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

static void *new_thread_start(void *arg)
{
    int ret;
    //!分离自身，分离后线程结束会自动被回收
    ret = pthread_detach(pthread_self());
    if (ret)
    {
        fprintf(stderr, "pthread_detach error: %s\n", strerror(ret));
        return NULL;
    }

    printf("新线程开始\n");
    sleep(2);
    printf("新线程结束\n");
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid;
    int ret;

    ret = pthread_create(&tid, NULL, new_thread_start, NULL);
    if (ret)
    {
        fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
        exit(-1);
    }

    sleep(1);

    ret = pthread_join(tid, NULL);
    if (ret)
    {
        fprintf(stderr, "pthread_join error: %s\n", strerror(ret));
    }

    pthread_exit(NULL);
}