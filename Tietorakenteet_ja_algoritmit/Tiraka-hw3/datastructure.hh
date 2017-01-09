// Definition of Datastructure class, hw3 of TIE-20100/TIE-20106

#ifndef DATASTRUCTURE_HH
#define DATASTRUCTURE_HH

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <memory>

using namespace std;

const std::string NO_ROUTE = "Error: No route!";
const std::string NO_SUCH_STOP = "Error: No such stop!";

class Datastructure
{
public:
    Datastructure();

    ~Datastructure();

    // Add a new bus stop
    void add_stop(int stop_id, std::string stop_name);

    // Add a new bus route
    void add_route(int route_id, std::string route_name);

    // Add a new stop to a route (both the route and the stop have already been added
    // using add_route and add_stop)
    void add_stop_to_route(int route_id, int stop_id, unsigned int minutes);

    // Add a new bus driving a route (the route has already been added using add_route) leaving at a certain
    // time from the terminus (first stop on route)
    void add_bus(int bus_id, int route_id, unsigned int start_hours, unsigned int start_minutes);

    // Empty the datastructure
    void empty();

    // Print information on a bus stop
    void print_stop(int stop_id);

    // Print buses leaving from a stop
    void print_buses(int stop_id);

    // Print the number of stops, bus routes, and buses
    void print_statistics();

    // Print out the fastest journey leaving from stop start_stop to stop end_stop. Journey starts at the given time
    // and the whole journey must be done within the same day (before midnight).
    void print_fastest_journey(int start_stop, int end_stop, unsigned int hours, unsigned int minutes);

    // Copy constructor is forbidden
    Datastructure(const Datastructure&) = delete;
    // Assignment operator is forbidden
    Datastructure& operator=(const Datastructure&) = delete;

private:

    // Add your own implementation here
    struct route;
    struct pathtoStop;
    //Data for a bus.
    struct bus{
        int bus_id;
        int route_id;
        route* route_pointer;
        std::string route_name;
        unsigned int start_hours;
        unsigned int start_minutes;
    };
    std::vector<bus*> allBuses;

    //Data of a single stop.
    struct stop{
        int stop_id;
        std::string stop_name;
        std::vector<std::pair<bus*, std::pair<unsigned int, unsigned int>>> buses;
        pathtoStop* currentPath;
    };
    std::vector<stop*> allStops;
    //Data of an entire route.
    struct route{
        int route_id;
        std::string route_name;
        std::vector<std::pair<stop*, unsigned int>> stops;
    };
    std::vector<route*> allRoutes;

    //Data for a path.
    struct path1{
        int etaisyys;
        unsigned int hours;
        unsigned int minutes;
        stop* pathStop;
        bus* bus1;
        bus* edellinen_Bussi;
        path1* next;
    };
    void findPath(stop* startStop, int endStop, unsigned int hours, unsigned int minutes, pathtoStop *);
 //   std::shared_ptr<path1> findPath(stop* startStop, int endStop, unsigned int hours, unsigned int minutes, int etaisyys);
    path1 * findPath(stop *startStop, int endStop, unsigned int hours, unsigned int minutes, int etaisyys);
    std::vector<stop*> visitedPointers;
    //Data for path to stop.
    struct pathtoStop{
        unsigned int hours;
        unsigned int minutes;
        std::vector<std::pair<stop*, bus*>> links;
    };
};

#endif // DATASTRUCTURE_HH
