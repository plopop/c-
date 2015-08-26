#include <iostream>
#include <thread>
#include <stdexcept>

#include "hierarchial_mutex.h"

using namespace std;

void test(int id, unsigned int level)
{
    hierarchical_mutex hm1(1500);
    hierarchical_mutex hm2(level);
    try
    {
        std::cout << 1 << "waiting lock.." << std::endl;

        hm1.try_lock();
        std::cout << 2 << "waiting lock.." << std::endl;

        hm2.try_lock();


//        std::cout << id << "locked.." << std::endl;
        hm1.unlock();
        hm2.unlock();
        std::cout << id << "unlocked" << std::endl;

    }
    catch (std::logic_error &e)
    {
        std::cerr << "*****caught " << e.what() << std::endl;

    };
}

int main()
{
    std::thread t1(test, 1, 1000);

    t1.join();

    return 0;
}

