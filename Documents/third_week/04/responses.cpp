#include "responses.h"
using namespace std;

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
