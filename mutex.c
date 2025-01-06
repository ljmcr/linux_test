#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_COUNT 20000
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * thread_func(void * arg) {
    int *p = (int *)arg;

    // 在累加之前获取锁，保证只有一个线程同一时间在累加
    pthread_mutex_lock(&mutex);

    (*p)++;

    //释放锁
    pthread_mutex_unlock(&mutex);

    return (void *)0;
}

int main(int argc, char cosnt *argv[])
{
    pthread_t pid[THREAD_COUNT];
    int num = 0;
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        // 创建线程，功能是给传入的参数加1
        pthread_create(pid + i, NULL, thread_func, &num);
    }

    // 等待所有线程结束
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(pid[i], NULL);
    }

    printf("num = %d\n", num);

    return 0;
}