#ifndef RELATIONALBROKER_H
#define RELATIONALBROKER_H
#include <mysql++/mysql++.h>

class RelationalBroker
{
public:
    RelationalBroker();
    void initDataBase();

    mysqlpp::StoreQueryResult query(std::string command);
    void update(std::string command);

private:
    static std::unique_ptr<mysqlpp::Connection> m_connection;
};

#endif
