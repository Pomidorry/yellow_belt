#pragma once
#ifndef QUERY_H_INCLUDED
#define QUERY_H_INCLUDED
#include <string>
#include <vector>
#include <sstream>
enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    std::string bus;
    std::string stop;
    std::vector<std::string> stops;
};

std::istream& operator >> (std::istream& is, Query& q);

#endif // QUERY_H_INCLUDED
