#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include<functional>
#include<algorithm>

using namespace std;

class some_data{
public:
    void do_something(){
//        std::lock_guard<std::mutex> l(m);
        data++;
        std::cout << "some_data.data: " <<data <<std::endl;
    }

private:
    int data = 5;
//    std::mutex m;
};

class data_wrapper {
public:
    template<typename Fun>
    void process_data(Fun func)
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        func(data);
        data.do_something();
    }

private:
    some_data data;
    std::mutex m_mutex;
};

some_data data;
void malicious_function(some_data protected_data)
{
    data = protected_data;
}

//数据不一致
//some_data *data;
//void malicious_function(some_data &protected_data)
//{
//    data = &protected_data;
//}

data_wrapper X;








//线程安全堆栈的示范
//typedef pthread_mutex_t MKIT_MUTEX_SECTION;

#include <sys/time.h>
#include <vector>
//#include <iterator>
#include <algorithm>
#include <stack>

pthread_cond_t g_timer_cond;
pthread_mutex_t g_timer_mutex;
#define THREAD_NUM 20
int order = 0;

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
        timeout.tv_nsec = (temp_timeout.tv_usec + m_time * 1000) * 1000;
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


threadsafe_stack<int> tss;



void do_work(int i)
{
//    std::cout << "i = " << i << std::endl;
    tss.push(i);

}

void f()
{
    std::vector<std::thread> threads;

    for(unsigned i = 0; i < 10; i++)
    {
//        threads.push_back(std::thread(do_work, i));
        std::thread t(do_work, i);
        threads.push_back (std::move(t));
    }

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

}


//在交换操作中使用std::lock()和std::lock_guard
class some_big_object
{
private:
    int m_val;
public:
    some_big_object(int val) : m_val(val) {}
    int getVal() const
    {
        return m_val;
    }
    void setVal(int val)
    {
        m_val = val;
    }
};

void swap(some_big_object& lhs, some_big_object& rhs);
//{
//    int tmp = lhs.getVal ();
//    lhs.setVal (rhs.getVal ());
//    rhs.setVal (tmp);
//}

class X
{
private:
    some_big_object some_detail;
    std::mutex m;
public:
    X(some_big_object const& sd) : some_detail(sd) {}
    friend void swap(X& lhs, X& rhs)
    {
        if (&lhs == &rhs)
            return;
        std::lock(lhs.m, rhs.m);
        std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
        std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);
        swap(lhs.some_detail, rhs.some_detail);
    }
};

int main(void)
{


//    std::thread th(&some_data::do_something, &data);
//    X.process_data(malicious_function);
//    data.do_something();

//    th.join();

    some_big_object lhs(1);
    some_big_object rhs(2);
//    X x1(lhs);
//    std::cout << "befor swap(), l: " << lhs.getVal () << " , r: " << rhs.getVal () << "\n";
//    X x1(lhs);
//    X x2(rhs);
//    swap(x1, x2);
//    std::cout << "after swap(), l: " << lhs.getVal () << " , r: " << rhs.getVal () << "\n";
    f();

    return 0;
}

