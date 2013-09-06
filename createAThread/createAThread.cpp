extern "C"
{
    #include <pthread.h>
    #include <unistd.h>
}

#include <iostream>

using namespace std;

void * function1(void * argument);
void * function2(void * argument);

int main()
{
    pthread_t t1,t2;
    pthread_create(&t1, NULL, function1, NULL);
    pthread_create(&t2, NULL, function2, NULL);

    //sleep(3);
    pthread_exit(NULL);

    return 0;
}

void * function1(void * argument)
{
    cout << " hello " << endl;
    sleep(2);
    return 0;
}

void * function2(void * argument)
{
    cout << " world " << endl;
    return 0;
}

