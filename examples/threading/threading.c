#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{
    struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    usleep(thread_func_args->wait_rx*1000);
    pthread_mutex_lock(thread_func_args->mutex);
    usleep(thread_func_args->wait_tx*1000);
    pthread_mutex_unlock(thread_func_args->mutex);

    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_rx, int wait_tx)
{
    struct thread_data data;
    data.wait_rx = wait_rx;
    data.wait_tx = wait_tx;
    threadfunc(&data);
    return false;
}

