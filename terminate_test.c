#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct Result {
    char *p;
    int len;
} Result;

// 如果一个进程的多个线程同时使用到标准的输入输出 会造成冲突的问题 导致只能有一个线程使用搭配标准的输入输出

void * pid_1_thread(void * arg) {
    // 初始化Reult结构体
    Result *result = (Result *)malloc(sizeof(Result));
    // 解析传递的参数
    char code = *((char *) arg);
    // 声明存放读取消息的字符串
    char *ans = malloc(101); 
    while (1) {
        fgets(ans, 100, stdin);
        if (ans[0] == code) {
            // 接到了回复消息
            free(ans);
            printf("pid_1_thread exit.\n");
            char *redans = strdup("pid_1_thread exit.");
            result->p = redans;
            result->len = strlen(redans);

            // 结束线程，返回
            pthread_exit((void *)result);
        } else {
            printf("pid_1_thread still running.\n");
        }
    }
}

void * pid_2_thread(void * arg) {
    // 初始化Reult结构体
    Result *result = (Result *)malloc(sizeof(Result));
    // 解析传递的参数
    char code = *((char *) arg);
    // 声明存放读取消息的字符串
    char *ans = malloc(101); 
    while (1) {
        fgets(ans, 100, stdin);
        if (ans[0] == code) {
            // 接到了回复消息
            free(ans);
            printf("pid_2_thread exit.\n");
            char *redans = strdup("pid_2_thread exit.");
            result->p = redans;
            result->len = strlen(redans);

            // 结束线程，返回
            pthread_exit((void *)result);
        } else {
            printf("pid_2_thread still running.\n");
        }
    }
}

int main(int argc, char const *argv[])
{
    // 创建两个线程
    char p1_code = 'r';
    char p2_code = 'w';

    pthread_t pid_1;
    pthread_t pid_2;
    pthread_create(&pid_1, NULL, pid_1_thread, &p1_code);
    pthread_create(&pid_2, NULL, pid_2_thread, &p2_code);

    Result *result_1 = NULL;
    Result *result_2 = NULL;

    pthread_join(pid_1, (void **)&result_1);
    printf("pid_1_thread return: %s\n", result_1->p);
    pthread_join(pid_2, (void **)&result_2);
    printf("pid_2_thread return: %s\n", result_2->p);

    return 0;
}