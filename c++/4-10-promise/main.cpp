#include <iostream>
#include <future>

#include <string>
#include <vector>
#include <iterator>


class data_packet
{
private:
    int id;
};

class Connection
{
private:
    int id;
    data_packet incoming_data;
    data_packet outgoing_data;
    bool m_has_income_data;
    bool m_has_outgoing_data;

public:
    bool has_incoming_data()
    {
        return m_has_income_data;
    }
    bool has_outgoing_data()
    {
        return m_has_outgoing_data;
    }

    data_packet incoming()
    {
        return incoming_data;
    }

};

using connection_set = std::vector<Connection>;
using connection_iterator = std::vector<Connection>::iterator;

bool donework(connection_set &connections)
{
    static int i = 0;
    return connections.empty() && i <= 10;
}

void process_connections(connection_set &connections)
{
    while (!donework(connections))
    {
        for (connection_iterator connection = connections.begin(), end = connections.end();
             connection != end;
             ++connection)
        {
            if (connection->has_incoming_data())
            {
                data_packet data = connection->incoming();
                auto p = connection->get_promise(data.id);
                p.set_value(data.payload);
            }
        }
    }
}

int main()
{

    return 0;
}

