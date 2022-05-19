#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

//mutex mtx;

void work()
{
    //mtx.lock();
    for (int i = 0; i < 5; ++i)
    {
        cout << "ID Thread = " << this_thread::get_id() << "\tCOUNT = " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    //mtx.unlock();
}

int main()
{
    thread t1(work);
    thread t2(work);

    t1.join();
    t2.join();

    return 0;
}
