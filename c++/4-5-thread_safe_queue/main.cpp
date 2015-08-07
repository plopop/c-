#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <thread>
#include <time.h>
#include <random>
#include <functional>

//using namespace std;

template<typename T>
class threadsafe_queue
{
private:
    mutable std::mutex mut;
    std::queue<T> data_queue;
    std::condition_variable data_cond;
public:
    threadsafe_queue()
    {}
    threadsafe_queue(threadsafe_queue const &other)
    {
        std::lock_guard<std::mutex> lk(other.mut);
        data_queue = other.data_queue;
    }
    void push(T &&new_value)
    {
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(new_value);
        data_cond.notify_one();  //唤醒一个wait线程
    }
    void wait_and_pop(T &value)
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]{return !data_queue.empty();});
        value = data_queue.front();
        data_queue.pop();
    }
    std::shared_ptr<T> wait_and_pop()
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]{return !data_queue.empty();});
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }
    bool try_pop(T &value)
    {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty())
            return false;
        value = data_queue.front();
        data_queue.pop();
        return true;
    }
    std::shared_ptr<T> try_pop()
    {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty())
            return std::shared_ptr<T>();  //?
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }
    bool empty() const
    {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }
};

class data_chunk
{
private:
//    A *p;
    int *a;
    const static int total = 50;  //?
    //随机数
//    std::default_random_engine generator(time(NULL));    //<random>
//    std::uniform_int_distribution<int> dis(0, 100);  //<random>
public:
    data_chunk()
    {
//        p = new A;
        a = new int[total];
//        auto dice = std::bind(dis, generator);   //<functional>

        for (int i = 0; i < total; ++i)
        {
//            *(a + i) = dice();
             *(a + i) = i;
        }
    }
    ~data_chunk()
    {
        if (a)
            delete [] a;
//        delete []b;
        std::cout << "\n~data_chunk()";
//        delete []p;
    }
    data_chunk operator = (data_chunk) = delete;
    void printData()
    {
        for (int i = 0; i < total; ++i)
        {

            std::cout << i << '\t';
//            std::cout << *(a + i);
        }
        std::cout << std::endl;
    }
};

int total = 0;
threadsafe_queue<data_chunk> tsq;

bool more_data_to_prepare()
{
    return total++ < 5000;
}

data_chunk *prepare_data()
{
    return new data_chunk();
}

void data_preparation_thread()
{
    while (more_data_to_prepare())
    {
        data_chunk *dc = prepare_data();
        tsq.push(std::move(*dc));
    }
}

void process(std::shared_ptr<data_chunk> data)
{
    data->printData();
}

void data_processing_thread()
{
    while (true)
    {
        std::shared_ptr<data_chunk> data = tsq.wait_and_pop();  //自动析构
        process(data);
    }
}

void f()
{
    double *d = new double[1000];
    delete [] d;
}

int main()
{


//    for (int i = 0; i < 1000000000; ++i)
//    {


//    data_chunk *d = new data_chunk[10];
//    delete [] d;

////        f();


////    d[0].printData();
//    std::cout << i << std::endl;
//    }

//    std::thread prepare_thread(data_preparation_thread);
//    std::thread process_thread(data_processing_thread);

//    prepare_thread.join();
//    process_thread.join();


    int *i = new int{11};
    std::cout << (unsigned long) i<< '\t' << *i << std::endl;
    delete i;
    std::cout << (unsigned long) i<< '\t' << *i << std::endl;

    return 0;
}

