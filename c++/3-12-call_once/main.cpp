#include <iostream>
#include <mutex>
#include <map>
#include <string>
#include <boost/thread/shared_mutex.hpp>
#include <iterator>

using namespace std;


class dns_entry
{
public:
//    dns_entry second;
    int a;
};
class dns_details
{
    int a;

};

//class connection_info;

//class X
//{
//private:
//    connection_info connection_details;


//    std::once_flag connection_init_flag;

//    void open_connection()
//    {
//        connection = connection_magageer.open
//    }
//};




class dns_cache
{
    std::map<std::string, dns_entry> entries;
    mutable boost::shared_mutex entry_mutex;
public:
    dns_entry find_entry(std::string const &domian) const
    {
        boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
        std::map<std::string, dns_entry>::const_iterator const it = entries.find(domian);
        return (it == entries.end()) ?  dns_entry() : it->second;
    }
    void update_or_andd_entry(std::string const &domain, const dns_entry &dns_details)
    {
        std::lock_guard<boost::shared_mutex> lk(entry_mutex);
        entries[domain] = dns_details;
    }

};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}

