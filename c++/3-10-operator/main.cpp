#include <iostream>
#include <mutex>

using namespace std;

class Y
{
private:
    int some_detail;
    mutable std::mutex m;

    int get_detail() const
    {
        std::lock_guard<std::mutex> lock_a(m);
        return some_detail;
    }
public:
    Y(int sd) : some_detail(sd) {}
    friend bool operator == (Y const &lhs, Y &rhs)
    {
        if (&lhs == &rhs)
            return true;
        int const lhs_value = lhs.get_detail();
        int const rhs_value = rhs.get_detail();
        return lhs_value == rhs_value;
    }
};

int main()
{
    Y y1(1);
    Y y2(2);

    std::cout << (y1 == y2 ? "yes" : "no") << std::endl;
    return 0;
}

