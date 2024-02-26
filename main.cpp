#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex testMutex;

int a = 0;
int b = 0;

void plusik(){

    unique_lock<std::mutex> lock1(testMutex);

    for(int i = 0; i < 100000; i++){
        a = a + 1;
    }

    lock1.unlock();
}

void minusik(){

    unique_lock<std::mutex> lock2(testMutex);

    for(int i = 0; i < 100000; i++){
        b = b - 1;
    }

    lock2.unlock();
}

int main()
{
    thread t1(plusik);
    thread t2(plusik);

    thread t3(minusik);
    thread t4(minusik);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    cout << "Result: a + b =  " << a + b << endl;
    // Если программа работает корректно, то a + b = 0

    return 0;
}
