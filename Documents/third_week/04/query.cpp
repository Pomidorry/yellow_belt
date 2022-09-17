#include "query.h"
using namespace std;

istream& operator >> (istream& is, Query& q) {
    string com;
    is >> com;
    if (com == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> q.bus;
        size_t s;
        is >> s;
        q.stops.resize(s);
        for (auto& item : q.stops)
        {
            is >> item;
        }
    }
    if (com == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.bus;
    }
    if (com == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.stop;
    }
    if (com == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}
