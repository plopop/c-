#include <iostream>
#include <mutex>

using namespace std;

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

void swap(some_big_object& lhs, some_big_object& rhs)
{
    int tmp = lhs.getVal ();
    lhs.setVal (rhs.getVal ());
    rhs.setVal (tmp);
}

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
    some_big_object getData() const
    {
        return some_detail;
    }
};

int main(void)
{

    some_big_object lhs(1);
    some_big_object rhs(2);
    X x1(lhs);
    X x2(rhs);
    std::cout << "befor swap(), l: " << x1.getData ().getVal () << " , r: " << x1.getData ().getVal () << "\n";
    swap(x1, x2);   //?
    std::cout << "after swap(), l: " << x1.getData ().getVal () << " , r: " << x1.getData ().getVal () << "\n";

    return 0;
}

