#include <iostream>
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

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

struct BusesForStopResponse {
    vector<string> buses_to_stop;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.buses_to_stop.empty()) {
        os << "No stop" << endl;
    }
    else {
        for (const auto& i : r.buses_to_stop) {
            os << i << " ";
        }
        os << endl;
    }
    return os;
}

struct StopsForBusResponse {
    string bus;
    vector < pair<string, vector<string>>> stops_for_bus;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.stops_for_bus.empty()) {
        os << "No bus" << endl;
    }
    else {
        for (const auto& i : r.stops_for_bus) {
            os << "Stop " << i.first << ": ";
            if (i.second.size() == 1)
            {
                os << "no interchange";
            }
            else
            {
                for (const auto& other_bus : i.second)
                {
                    if (other_bus != r.bus)
                    {
                        os << other_bus << " ";
                    }
                }
            }
            os << endl;
        }
    }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.buses_to_stops.empty())
    {
        os << "No buses" << std::endl;
    }
    else
    {
        for (const auto& bus_item : r.buses_to_stops)
        {
            os << "Bus " << bus_item.first << ": ";
            for (const std::string& stop : bus_item.second)
            {
                os << stop << " ";
            }
            os << std::endl;
        }
    }
    return os;
}
class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops[bus] = stops;
        for (const auto& stop : stops) {
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        if (stops_to_buses.count(stop) == 0)
        {
            return BusesForStopResponse{ };
        }
        else
        {
            return BusesForStopResponse{ stops_to_buses.at(stop) };
        }
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        vector<pair<string, vector<string>>> result;
        if (buses_to_stops.count(bus) > 0)
        {
            for (const auto& stop : buses_to_stops.at(bus))
            {
                result.push_back(make_pair(stop, stops_to_buses.at(stop)));
            }
        }
        return StopsForBusResponse{ bus, result };
    }

    AllBusesResponse GetAllBuses() const {
        return AllBusesResponse{buses_to_stops};
    }
private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}

