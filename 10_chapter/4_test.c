//!线程清理函数的添加、删除与手动触发
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
//!线程清理函数
static void cleanup(void *arg)
{
    printf("cleanup: %s\n", (char*)arg);
}

static void *new_thread_start(void *arg)
{
    printf("新线程开始\n");
    //!向栈底添加清理函数，第一个参数为绑定的函数名，第二个参数为清理函数的参数，必须与pop函数配对使用
    pthread_cleanup_push(cleanup, "第1次调用");
    pthread_cleanup_push(cleanup, "第2次调用");
    pthread_cleanup_push(cleanup, "第3次调用");
    
    //!括号内为非零值时移除并执行栈顶的（即最后添加的）清理函数，必须与push函数配对使用
    pthread_cleanup_pop(1);
    printf("~~~~~~~~~~~~~~\n");
    
    sleep(2);
    
    pthread_exit((void*)0);

    //!括号内为零时仅移除栈顶的清理函数，必须与push函数配对使用，并且位于线程终止语句后
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
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

    sleep(1);

    ret = pthread_join(tid, &tret);
    if (ret)
    {
        fprintf(stderr, "pthread_join error: %s\n", strerror(ret));
    }

    printf("新线程结束，code=%ld\n", (long)tret);

    pthread_exit(NULL);
}