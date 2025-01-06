#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void *task(void *arg)
{
    printf("thread started.\n");
    // 默认取消类型是DEFERRED
    printf("working...\n");
    sleep(1);
    // 人为调用取消点函数
    pthread_testcancel();
    printf("thread end.\n");
    return NULL;
}

int main(int argc, char const *argv[])
{
    // 创建线程
    pthread_t tid;
    pthread_create(&tid, NULL, task, NULL);

    // 取消子线程
    if (pthread_cancel(tid) != 0) {
        perror("pthread_cancel");
        exit(EXIT_FAILURE);
    }

    // pthread_cancel 只是发出一个停止命令，不会立即停止线程
    // join会等待线程结束，获取线程的返回值
    void *res;
    pthread_join(tid, &res);
    if (res == PTHREAD_CANCELED) {
        printf("thread was canceled.\n");
    } else {
        printf("thread was not canceled, exit code is %ld\n", (long)res);
    }

    return 0;
}