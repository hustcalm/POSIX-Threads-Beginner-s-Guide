extern "C"
{
    #include <pthread.h>
    #include <unistd.h>
}

#include <iostream>

using namespace std;

const int NUMBER_OF_THREADS = 5;

int some_value = 10;

pthread_mutex_t mutex_for_some_value = PTHREAD_MUTEX_INITIALIZER;


void* thread_talk(void* thread_nr)
{
    for(int x = 1; x < 500; x++)
    {
        // lock some_value here
        //pthread_mutex_lock(&mutex_for_some_value);

        some_value = some_value*10;
        some_value++;
        some_value--;
        some_value = some_value/10;

        //cout << "Now some_value is " << some_value << endl;

        // and unlock it for the next thread
        //pthread_mutex_unlock(&mutex_for_some_value);
    }

    pthread_exit(NULL);
    
    return 0;
}

int main(void)
{
    pthread_t thread[NUMBER_OF_THREADS];
    cout << "Starting all threads..." << endl;
    
    int temp_arg[NUMBER_OF_THREADS];

    for(int current_t = 0; current_t < NUMBER_OF_THREADS; current_t++)
    {
        temp_arg[current_t] = current_t;

        int result = pthread_create(&thread[current_t], NULL, thread_talk, static_cast<void*>(&temp_arg[current_t]));
        if(result != 0)
        {
            cout << "Error creating thread " << current_t << ". Return code:" << result << endl;
        }
    }

    for(int current_t = 0; current_t < NUMBER_OF_THREADS; current_t++)
    {
        pthread_join(thread[current_t], NULL);
    }

    cout << "All threads completed." << endl;
    cout << "The final some_value is " << some_value << endl;

    return 0;
}


