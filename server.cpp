#include "server.h"
#include <QDebug>
#include <nlohmann/json.hpp>
#include <iostream>
Server::Server() {}

void server::conversionJson(char *buf)
{
    auto j=nlohmann::json::parse(buf);
    std::cout<<"json object:"<<j.at("id")<<std::endl;
}
