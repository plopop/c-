#ifndef DATA_CHUNK
#define DATA_CHUNK

#include <iostream>
#include <random>
#include <functional>

//#include <memory>

class data_chunk
{
private:
    int *a;
    int total;

    //随机数
    std::default_random_engine generator;    //<random>
    std::uniform_int_distribution<int> dis;  //<random>


public:
    data_chunk()
    {
        a = new int[total];
        auto dice = std::bind(dis, generator);   //<functional>

        for (int i = 0; i < total; ++i)
        {
            *(a + i) = dice();
        }
    }
    ~data_chunk()
    {
        for (int i = 0; i < total; ++i)
            delete &a[i];
        delete [] a;
    }
};

#endif // DATA_CHUNK

