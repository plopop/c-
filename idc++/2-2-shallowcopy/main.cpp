#include <iostream>
#include <string.h>
#include <malloc.h>
#include <vector>

using namespace std;

class MyString
{
private:
    char* m_data;
    size_t m_len;
    void copy_data(const char *s)
    {
        m_data = new char[m_len + 1];
        memcpy(m_data, s, m_len);   //拷贝字节
        m_data[m_len] = '\0';
    }
public:
    MyString()
    {
        m_data = NULL;
        m_len = 0;
    }
    MyString(const char* p)
    {
        m_len = strlen(p);  //检测字符串长度
        copy_data(p);
    }




//    MyString(const MyString& str)
//    {
//        m_len = str.m_len;
//        copy_data(str.m_data);
//    }


//    MyString& operator = (const MyString& str)
//    {
//        if (this != &str)
//        {
//            m_len = str.m_len;
//            copy_data(str.m_data);
//        }
//        std::cout << "copy assignment is called! source: " << str.m_data << endl;
//        return *this;
//    }

    MyString(MyString&& str)    //移动构造
    {
        std::cout << "Move constructor is called! source: " << str.m_data << std::endl;
        m_len = str.m_len;
        m_data = str.m_data;
        str.m_len = 0;
        str.m_data = NULL;
    }
    MyString& operator = (MyString&& str)
    {
        std::cout << "move assignment is called! source: " << str.m_data << std::endl;
        if (this != &str)
        {
            m_len = str.m_len;
            m_data = str.m_data;
            str.m_len = 0;
            str.m_data = NULL;
        }
        return *this;
    }

    virtual ~MyString()
    {
        if (m_data)
//            free(m_data);
            delete(m_data);
    }
};

int main()
{
    MyString s;
    s = MyString("hello");
    std::vector<MyString> vec;
    vec.push_back(MyString("World"));
    return 0;
}

