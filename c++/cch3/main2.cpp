#include <iostream>
#include <mutex>
//线程安全堆栈的示范
#include <exception>
#include <memory>
#include <stack>
#include <thread>

using namespace std;

class some_data
{
    int a;
    std::string b;
public:
    void do_something()
    {
        std::cout << "some_data.do_someting()";
    }
};

class data_wrapper
{
private:
    some_data data;
    std::mutex m;
public:
    template<typename Function>
    void process_data(Function func)
    {
        std::lock_guard<std::mutex> l(m);
        func(data);
    }
};
//传出被保护数据的引用
some_data* unprotected;
void malicious_function(some_data& protected_data)
{
    unprotected = &protected_data;
}
data_wrapper x;
void foo()
{
    x.process_data(malicious_function);
    unprotected->do_something ();
}

//线程安全堆栈的示范
//typedef pthread_mutex_t MKIT_MUTEX_SECTION;

#include <sys/time.h>
#include <vector>
//#include <iterator>
#include <algorithm>


pthread_cond_t g_timer_cond;
pthread_mutex_t g_timer_mutex;
#define THREAD_NUM 20

struct empty_stack: std::exception
{
    const char* what() const throw();
};
template<typename T>
class threadsafe_stack
{
private:
    std::stack<T> data;
    mutable std::mutex m;
    int m_time; //等待时间
public:
    threadsafe_stack(){}
    threadsafe_stack(const threadsafe_stack& other)
    {
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data;  //?私有成员
    }
    threadsafe_stack& operator= (const threadsafe_stack&) = delete;

    void push(T new_value)
    {
        std::lock_guard<std::mutex> lock(m);
        data.push (new_value);

        //延时测试
        std::cout << "waiting 2s for pushing " << new_value << "...";
        m_time = 2;
        struct timeval temp_timeout;
        gettimeofday(&temp_timeout, 0); //获取当前时间
        struct timespec timeout;
        timeout.tv_sec = temp_timeout.tv_sec;
        timeout.tv_nsec = (temp_timeout.tv_usec + m_time + 1000) * 1000;
        pthread_cond_timedwait (&g_timer_cond, &g_timer_mutex, &timeout);
        std::cout  << new_value << "pushed\n";
    }
    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty ())
            throw empty_stack();
        std::shared_ptr<T> const res(std::make_shared<T>(data.top ()));
        data.pop ();
        return res;
    }
    void pop(T& value)
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty ()) throw empty_stack();
        value = data.top ();
        data.pop ();
    }
    bool empty () const
    {
        std::lock_guard<std::mutex> lock(m);
        return data.empty ();
    }

};
void testtss(threadsafe_stack<int> &tss, int val)
{
    tss.push (val);
}



int main()
{
    //传出被保护数据的引用
    foo();

    //线程安全堆栈的示范
    threadsafe_stack<int> tss;

    std::vector<std::thread> threads(20);
    for (int i = 0; i < 20; i++)
    {
        std::thread t([&tss, i]{ tss.push (i);});
//        std::thread t(testtss, tss, i);
        threads.push_back (std::move(t));

//        threads.push_back (std::thread(testtss, tss, i));

//        threads.push_back (std::thread(
//                               [&tss, i] { tss.push (i);}
//        ));
    }

//    std::thread t( [&tss] { tss.push (1);});
//    t.join ();

//    iterator<std::vector<std::thread> iter;
//    for (int i = 0; i < THREAD_NUM; i++)
//    {
//        threads.at (i).join();
//    }

    std::for_each(threads.begin(), threads.end (), std::mem_fn(&std::thread::join));

    return 0;
}

