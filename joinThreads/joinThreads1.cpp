extern "C"
{
    #include <pthread.h>
}

#include <iostream>

using namespace std;

void * function(void * argument);

int main(void)
{
    pthread_t t1,t2;
    string msg1(" hello ");
    string msg2(" world ");

    int thread1 = pthread_create(&t1, NULL, function, reinterpret_cast<void*>(&msg1));
    if(thread1 != 0)
        cout << "error" << endl;

    int thread2 = pthread_create(&t2, NULL, function, reinterpret_cast<void*>(&msg2));
    if(thread2 != 0)
        cout << "error" << endl;

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}

void * function(void * argument)
{
    cout << *(reinterpret_cast<string*>(argument)) << endl;
    return 0;
}

