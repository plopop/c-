#include <iostream>
#include <mutex>
#include <queue>
#include <condition_variable>

#include "data_chunk.h"

using namespace std;

std::mutex mut;
std::queue<data_chunk*> data_queue;
std::condition_variable data_cond;  //<condition_variable>
int num;

bool more_data_to_prepare()
{
    return num < 100;
}

data_chunk *prepare_data()
{
    return new data_chunk();

}

void data_preparation_thread()
{
    while (more_data_to_prepare())
    {
        data_chunk *data = prepare_data();
        data_queue.push(data);
    }
}

void data_process_thread()
{
    while (true)
    {
        data_chunk data;
//        data_queue.w
    }
}

int main(int arc, char *argv[])
{
    cout << "Hello World!" << endl;
    return 0;
}

