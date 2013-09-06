extern "C"
{
    #include <pthread.h>
}

#include <iostream>

using namespace std;

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;

void* function1(void* arg);
void* function2(void* arg);

int count = 0;
const int COUNT_DONE = 10;

int main(void)
{
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, &function1, NULL);
    pthread_create(&thread2, NULL, &function2, NULL);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    cout << "Final count is " << count << endl;

    return 0;
}

void* function1(void* arg)
{
    for(;;)
    {
        pthread_mutex_lock(&count_mutex);

        pthread_cond_wait(&condition_var, &count_mutex);

        cout << "function1 looks at count (" << count << ") and just adds 1 to it." << endl;
        count++;

        pthread_mutex_unlock(&count_mutex);

        if(count >= COUNT_DONE)
        {
            cout << "Count done in thread1 and will exit the thread." << endl;
            pthread_exit(NULL);
        }
    }
}

void* function2(void* arg)
{
    for(;;)
    {
        pthread_mutex_lock(&count_mutex);

        if(count & 1)
        {
            cout << "function2 detected count (" << count << ") is odd, so it adds 1 to it." << endl;
            count++;
        }
        else
        {
            pthread_cond_signal(&condition_var);
        }

        pthread_mutex_unlock(&count_mutex);

        if(count >= COUNT_DONE) 
        {
            cout << "Count done in thread2 and will exit the thread." << endl;

            // For debug, thread1 will not exit after thread2 terminating itself
            pthread_cond_signal(&condition_var);

            pthread_exit(NULL);
        }
    }
}

