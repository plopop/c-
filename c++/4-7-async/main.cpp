
#include <iostream>
#include <future>


using namespace std;

bool dosomething(int i)
{
    std::cout << "dosomething(): start\n";
    std::this_thread::sleep_for(std::chrono::seconds(i));
    std::cout << "dosomething(): completed\n";
    return true;
}

int main()
{
    std::cout << "main(): allocating task\n";
//    std::future<bool> result = std::async(dosomething, 2);
    std::future<bool> result = std::async(std::launch::async, dosomething, 4);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "mian(): getting answer...\n";
    std::cout << result.get() << std::endl;

    return 0;
}

