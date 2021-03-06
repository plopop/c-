#ifndef HIERARCHIAL_MUTEX
#define HIERARCHIAL_MUTEX

#include <iostream>
#include <mutex>

using std::mutex;

class hierarchical_mutex
{
    std::mutex internal_mutex;
    unsigned long const hierarchy_value;
    unsigned long previous_hierarchy_value;
    static thread_local unsigned long this_thread_hierarchy_value;

    void check_for_hierarchy_violation()
    {
        if (this_thread_hierarchy_value <= hierarchy_value)
        {
            throw std::logic_error("mutex hierarchy violated");
        }
    }
    void update_hierarchy_value()
    {
        previous_hierarchy_value = this_thread_hierarchy_value;
        this_thread_hierarchy_value = hierarchy_value;
    }
public:
    explicit hierarchial_mutex(unsigned long value) :
        hierarchy_value(value),
        previous_hierarchy_value(0)
    {}
    void lock()
    {
        check_for_hierarchy_violation ();
        internal_mutex.lock ();
        update_hierarchy_value ();
    }

    void unlock()
    {
        this_thread_hierarchy_value = a;

    }
};

#endif // HIERARCHIAL_MUTEX

