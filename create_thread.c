#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_LEN 1024

char *buf;

// 读线程需要执行的代码逻辑
void *input_thread(void *arg)
{
    int i = 0;
    while (1)
    {
        // 读取控制台输入
        char c = fgetc(stdin);
        if (c && c != '\n') {
            buf[i++] = c;
        }

        if (i >= BUF_LEN) {
            i = 0;
        }
    }

    return NULL;
}

void output_thread(void *arg) {
    int i = 0;
    while (1)
    {
        // 读取一个字节，写出到控制台，换行
        if (buf[i]) {
            fputc(buf[i], stdout);
            fputc('\n', stdout);
            buf[i++] = 0;

            // 读取数据到了最大下标
            if (i >= BUF_LEN) {
                i = 0;
            }
        } else {
            // 没有数据，休眠一段时间
            sleep(1);
        }
    }
}

// 两个线程
// 1号读取控制台信息 写入到缓存中
// 2号将缓存信息写出到控制台

int main(int argc, char const *argv[])
{
    buf = malloc(BUF_LEN);
    
    // 声明线程id
    pthread_t pid_input;
    pthread_t pid_output;

    // 创建读线程
    pthread_create(&pid_input, NULL, input_thread, NULL);
    // 创建写线程
    pthread_create(&pid_output, NULL, output_thread, NULL);

    // 主线程等待读写线程结束
    pthread_join(pid_input, NULL);
    pthread_join(pid_output, NULL);

    free(buf);
}