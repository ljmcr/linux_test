#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_rwlock_t rwlock;
// 动态初始化读写锁
// pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
int shared_data = 0;

void writer_thread(void *arg)
{
    int tmp = shared_data + 1;
    sleep(1);
    shared_data = tmp;
    printf("current writer thread: %s, shared_data: %d\n", (char *)arg, shared_data);
}

void reader_thread(void *arg)
{
    pthread_rwlock_rdlock(&rwlock);
    printf("current reader thread: %s, shared_data: %d\n", (char *)arg, shared_data);
    pthread_rwlock_unlock(&rwlock);
}

int main(int argc, char const *argv[])
{
    // 显示初始化读写锁
    pthread_rwlock_init(&rwlock);

    pthread_t writer1, writer2, reader1, reader2, reader3, reader4, reader5, reader6;

    // 创建写线程
    pthread_create(&writer1, NULL, (void *)writer_thread, "writer1");
    pthread_create(&writer2, NULL, (void *)writer_thread, "writer2");

    // 休眠等待
    sleep(3);
    // 创建读线程
    pthread_create(&reader1, NULL, (void *)reader_thread, "reader1");
    pthread_create(&reader2, NULL, (void *)reader_thread, "reader2");
    pthread_create(&reader3, NULL, (void *)reader_thread, "reader3");
    pthread_create(&reader4, NULL, (void *)reader_thread, "reader4");
    pthread_create(&reader5, NULL, (void *)reader_thread, "reader5");
    pthread_create(&reader6, NULL, (void *)reader_thread, "reader6");

    // 销毁读写锁
    pthread_rwlock_destroy(&rwlock);


    return 0;
}