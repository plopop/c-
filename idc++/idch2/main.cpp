#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>

////2-1输出引用类型
//#include <type_traits>
//#include <typeinfo>

//#ifdef _MSC_VER
//#include <cxxabi.h>
//#endif
//template <class T>
//std::string type_name()
//{
//    typedef typename std::remove_reference<T>::type TR;
//    std::unique_ptr<char, void(*)(void*)> own
//            (
//            #ifndef __GNUC__
//                nullptr,
//            #else
//                abi::__cxa_demangle(typeid(TR).name (), nullptr, nullptr, nullptr),
//            #endif
//                std::free
//                );
//    std::string r = own != nullptr ? own.get () : typeid(TR).name ();
//    if (std::is_const<TR>::value)
//        r += " const";
//    if (std::is_volatile<TR>::value)
//        r += " volatile";
//    else if (std::is_rvalue_reference<TR>::value)
//        r += "&&";
//    return r;
//}
//template<typename T>
//void Func(T&& t)
//{
//    std::cout << type_name<T>() << std::endl;
//}
//void TestReference()
//{
//    std::string str = "test";
//    Func (str);
//    Func (std::move(str));
//}

using namespace std;

void f(int&& i)
{
    i++;
    cout << i;
}

int main()
{
    int w1 = 11;
     int w2 = 22;
    auto& v1 = w1;
    auto v2 =v1;
    cout << v2;
//    decltype(w1) v3 =  w2;

    int& q = w1;
    int& r = q;

    r = w2;

    cout << v1 << q << r << w1;

    /*const*/ int i = 3;
    &i;
    f(/*move*/(22));
    cout << i;




    return 0;
}
