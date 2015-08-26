#include <iostream>
#include <utility>

using namespace std;

template<typename T>
void printT(T& t)
{
    std::cout << "lvalue";
}

template<typename T>
void printT(T && t)
{
    cout << "rvalue" << endl;
}

template<typename T>
void testForward(T &&v)
{
    printT(v);
    printT(std::forward<T>(v));
    printT(std::move(v));
}
int main()
{
    testForward(1);
    int x = 1;
    testForward(x);
    testForward(std::forward<int>(x));

    return 0;
}

