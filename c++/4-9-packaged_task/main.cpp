#include <iostream>
#include <deque>
#include <mutex>
#include <future>
#include <thread>
#include <utility>
#include <functional>


std::mutex m;
std::deque<std::packaged_task<void(int*)> > tasks;

bool gui_shutdown_message_received()
{
    static int i = 0;
    return ++i == 55;
//    return false;
}
void get_and_process_gui_message(int count)
{
//    std::cout << "get " << count << std::endl;
}

void gui_thread()
{
    static int count = 0;
    while (!gui_shutdown_message_received())
    {
        get_and_process_gui_message(++count);
        std::packaged_task<void(int*)> task;
        {
            std::lock_guard<std::mutex> lk(m);
            if (tasks.empty())
                continue;
            task = std::move(tasks.front());
            tasks.pop_front();
        }
        task(&count);   //优先使用默认参数？
    }
}

template<typename Func>
std::future<void> post_task_for_gui_thread(Func f)
{
    std::packaged_task<void(int*)> task(f);
    std::future<void> res = task.get_future();
    std::lock_guard<std::mutex> lk(m);
    tasks.push_back(std::move(task));
    return res;
}

void dotask(int *i)
{
    std::cout << "do task" << *i << std::endl;
}


class A
{
public:
    A() {}
    static void f(int *a)
    {
        std::cout << "in class A: " << *a << std::endl;

    }
};

//using namespace std::placeholders;
int main()
{
//    A a;
    std::thread gui_bg_thread(gui_thread);

    int *a = new int(1);

    for (int i = 0; i < 10; ++i)
    {

//        std::function<void(int*)> f1 = std::bind(A::f, std::placeholders::_1);
//        std::function<void(int*)> f = std::bind(dotask, std::placeholders::_1);
        std::function<void(int*)> f = std::bind(dotask, a);
        std::function<void(int*)> f1 = std::bind(dotask, std::placeholders::_1);

        post_task_for_gui_thread(f1);
        post_task_for_gui_thread(f);

    }

    gui_bg_thread.join();

    return 0;
}

