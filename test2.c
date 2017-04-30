#include <linux/unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#include <linux/kernel.h>
#define __NR_vmaStatistic 341

pthread_mutex_t    mutex_lock;


void * sthread( void *arg)
{
    pthread_mutex_unlock(&mutex_lock);
    pthread_mutex_lock(&mutex_lock);
    syscall(__NR_vmaStatistic, getpid());
    
}


int main(int argc, char *argv[])
{
    // create threads to test
    int threads = 2;
    int i;
    
    pthread_mutex_init(&mutex_lock, NULL);
    pthread_t threadMem[threads];
    
    // creates threads
    for( i = 0; i < threads; i++ )
    {
        pthread_create(&(threadMem[i]), NULL, (void *) sthread, NULL);
    }
    
    //makes sure thread execution has finished
    for( i = 0; i < threads; i++ )
    {
        if(threadMem[i] != 0)
        {
            pthread_join(threadMem[i],NULL);
        }
    }
    return 0;
}
