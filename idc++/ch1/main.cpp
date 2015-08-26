#include <iostream>
#include <thread>

using namespace std;

int &foo(int &i);
float foo(float &f);

template <typename T, typename U>
auto add(T &val) -> decltype(foo(val))
{
    return foo(val);
}


template <typename T>
using type_t = T;
type_t<int> i;

//默认模板参数
template <typename T, typename U = int, U N = 0>
struct Foo
{

};


void hello()
{
    cout << "hello concurrent world\n";
}

int main()
{
    int a = 1.1;
//    int b = { 1.1 };

    float fa = 1e40;
//    float fb = { 1e40 };

    float fc = (unsigned long long) -1;
//    float fd = { (unsigned long long) -1 };
    float fe = (unsigned long long) 1;
    float ff = { (unsigned long long) 1};

    const int x = 1024, y = 1;
//    char c = x;
//    char d = { x };
    char e = y;
    char f = { y};


    std::thread t(hello);
    t.join ();




     cout << "Hello World!" << endl;
    return 0;
}

