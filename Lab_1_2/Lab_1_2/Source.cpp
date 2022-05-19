#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

mutex mtx1;
mutex mtx2;
void work1()
{
    //Правильно
    mtx1.lock();

    //Deadlock
    //mtx2.lock();

    this_thread::sleep_for(chrono::milliseconds(1));
   
    //Правильно
    mtx2.lock();

    //Deadlock
    //mtx1.lock();

    for (int i = 0; i < 5; ++i)
    {
        cout << "ID Thread = " << this_thread::get_id() << "\tCOUNT = " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    
    //Правильно
    mtx2.unlock();

    //Deadlock
    //mtx1.unlock();

    //Правильно
    mtx1.unlock();

    //Deadlock
    //mtx2.unlock();
}
void work2()
{
    mtx1.lock();

    this_thread::sleep_for(chrono::milliseconds(1));

    mtx2.lock();

    for (int i = 0; i < 5; ++i)
    {
        cout << "ID Thread = " << this_thread::get_id() << "\tCOUNT = " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    mtx2.unlock();
    mtx1.unlock();
}

int main()
{
    thread t1(work1);
    thread t2(work2);

    t1.join();
    t2.join();

    return 0;
}
