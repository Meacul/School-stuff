// Definition of Datastructure class, hw3 of TIE-20100/TIE-20106

#include "datastructure.hh"
#include <string>
#include <map>
#include <vector>
#include <memory>

using namespace std;

Datastructure::Datastructure()
{
}


Datastructure::~Datastructure()
{
}

void Datastructure::add_stop(int stop_id, std::string stop_name)
{
    stop* tempStop = new stop;
    tempStop->stop_id = stop_id;
    tempStop->stop_name = stop_name;
    allStops.push_back(tempStop);
}

void Datastructure::add_route(int route_id, std::string route_name)
{
    route* tempRoute = new route;
    tempRoute->route_id = route_id;
    tempRoute->route_name = route_name;
    allRoutes.push_back(tempRoute);
}

void Datastructure::add_stop_to_route(int route_id, int stop_id, unsigned int minutes)
{
    size_t i = 0;
    route* tempRoute = NULL;
    route* rightRoute = NULL;
    while (i < allRoutes.size()) {
        tempRoute = allRoutes[i];
        if (tempRoute->route_id == route_id){
            rightRoute = tempRoute;
            i = allRoutes.size();
        }
        else{

        }
        i++;
    }
    if(rightRoute == NULL){
        cout << NO_ROUTE << endl;
    }
    else{
        std::pair<stop*, unsigned int> temp;
        size_t j = 0;
        stop* tempStop;
        stop* rightStop;
        while(j < allStops.size()){
            tempStop = allStops[j];
            if(tempStop->stop_id == stop_id){
                rightStop = tempStop;
                j = allStops.size();
            }
            else{
                j++;
            }
        }
        if(rightStop == NULL){
             cout << NO_SUCH_STOP << endl;
        }
        else{
            temp = make_pair(rightStop, minutes);
            rightRoute->stops.push_back(temp);
        }

    }

}

void Datastructure::add_bus(int bus_id, int route_id, unsigned int start_hours, unsigned int start_minutes)
{
    bus* tempBus = new bus;
    tempBus->bus_id = bus_id;
    tempBus->route_id = route_id;
    tempBus->start_hours = start_hours;
    tempBus->start_minutes = start_minutes;
    allBuses.push_back(tempBus);
    size_t i = 0;
    route* tempRoute = NULL;
    route* rightRoute = NULL;
    while(i < allRoutes.size()){
        tempRoute = allRoutes[i];
        if(tempRoute->route_id == route_id){
            rightRoute = tempRoute;
            i = allRoutes.size();
        }
        else{
            i++;
        }
    }

    if(rightRoute != NULL){
        tempBus->route_pointer = rightRoute;
        tempBus->route_name = rightRoute->route_name;
        stop* tempStop = NULL;
        size_t j = 0;
        while(j < rightRoute->stops.size()){
            tempStop = rightRoute->stops[j].first;
            pair<unsigned int, unsigned int> stopTime;
            unsigned int stopMinutes = start_minutes + rightRoute->stops[j].second;
            unsigned int stopHours = start_hours;
            while(stopMinutes >= 60){
                stopHours++;
                stopMinutes = stopMinutes - 60;
            }
            while(stopHours >= 24){
                stopHours = stopHours - 24;
            }
            stopTime = make_pair(stopHours, stopMinutes);
            pair<bus*, pair<unsigned int, unsigned int>> tempPair;
            tempPair = make_pair(tempBus, stopTime);
            if(tempStop->buses.empty()){
                tempStop->buses.push_back(tempPair);
            }
            else if(tempStop->buses.begin()->first->bus_id < tempBus->bus_id){
                tempStop->buses.insert(tempStop->buses.begin(), tempPair);
            }
            else{
                size_t k = 0;
                while (k < tempStop->buses.size()){
                    if(tempStop->buses.at(k).first->bus_id < tempBus->bus_id){
                        tempStop->buses.insert(tempStop->buses.begin()+k, tempPair);
                        k = tempStop->buses.size()+3;
                    }
                    else{
                        k++;
                    }
                }
                if(k != tempStop->buses.size() + 3){
                    tempStop->buses.push_back(tempPair);
                }
            }
            j++;
        }
    }
}

void Datastructure::empty()
{
    allBuses.empty();
    allRoutes.empty();
    allStops.empty();

}

void Datastructure::print_stop(int stop_id)
{
    stop* temp = NULL;
    stop* right = NULL;
    size_t i = 0;
    while(i < allStops.size()){
        temp = allStops[i];
        if (temp->stop_id == stop_id){
            right = temp;
            i = allStops.size();
        }
        else{
            i++;
        }
    }
    if(right == NULL){
        cout << NO_SUCH_STOP << endl;
    }
    else{
        cout << right->stop_name << endl;
    }
}

void Datastructure::print_buses(int stop_id)
{
    size_t i = 0;
    stop* tempStop = NULL;
    while(i < allStops.size()){
        if(allStops[i]->stop_id == stop_id){
            tempStop = allStops[i];
            i = allStops.size();
        }
        else{
            i++;
        }
    }
    if(tempStop == NULL){
        cout << NO_SUCH_STOP << endl;
    }
    else{
        size_t j = 0;
        while(j < tempStop->buses.size()){
            cout <<  tempStop->buses[j].first->route_name << endl;
            j++;
        }
    }
}

void Datastructure::print_statistics()
{
    cout << allStops.size() << " stops, " << allRoutes.size() << " routes, " << allBuses.size() <<
            " buses." << endl;
}

void Datastructure::print_fastest_journey(int start_stop, int end_stop, unsigned int hours, unsigned int minutes)
{
    visitedPointers.empty();
    size_t i = 0;
    stop* tempStop = NULL;
    while(allStops.size() > i)
    {
        if(allStops[i]->stop_id == start_stop)
        {
            tempStop = allStops[i];
            i = allStops.size();
        }
        else{
            i++;
        }
    }
    if(tempStop == NULL)
    {
        cout << NO_SUCH_STOP << endl;
    }
    else
    {
        pathtoStop* temp = new pathtoStop;
        temp->hours = hours;
        temp->minutes = minutes;
        size_t i = 0;
        while(i < allStops.size()){
            allStops[i]->currentPath = NULL;
            i++;
        }
        findPath(tempStop,end_stop,hours,minutes, temp);
    }
    tempStop = NULL;
    for(size_t i = 0; i < allStops.size(); i++){
        if(end_stop == allStops[i]->stop_id){
            tempStop = allStops[i];
        }
    }

    int bus1ID = 1;
    int bus2ID = 0;
    size_t j = 0;
    size_t k = 0;
    bus* tempBus = tempStop->currentPath->links[j].second;
    route* temproute = tempBus->route_pointer;
    pair<stop*, unsigned int> tempPair;
    while(k < temproute->stops.size()){
        if(temproute->stops[k].first->stop_id == tempStop->currentPath->links[j].first->stop_id){
            tempPair = temproute->stops[k];
            k = temproute->stops.size();
        }
        k++;
    }
    unsigned int tempMinutes = tempPair.first->currentPath->minutes + tempPair.second;
    while(tempMinutes > 60){
        tempPair.first->currentPath->hours++;
        tempMinutes = tempMinutes - 60;
    }
    tempPair.first->currentPath->minutes = tempMinutes;
    for(size_t i = 0; i < tempStop->currentPath->links.size(); i++){
        bus1ID = tempStop->currentPath->links[i].second->bus_id;
        if(i == j){
            cout << tempStop->currentPath->links[i].second->route_name << endl;
            bus2ID = bus1ID;
        }
        unsigned int tempHours = tempStop->currentPath->links[i].first->currentPath->hours;
        unsigned int tempMinutes = tempStop->currentPath->links[i].first->currentPath->minutes;
        int tempStopID = tempStop->currentPath->links[i].first->stop_id;
        string tempStopName = tempStop->currentPath->links[i].first->stop_name;
        cout << tempHours << ":"
             <<  tempMinutes << " "
             << tempStopID << ", "
             <<  tempStopName << endl;
        if(bus1ID != bus2ID){
            cout << tempStop->currentPath->links[i].second->route_name << endl;
            size_t l = 0;
            route* tempRouteP = tempStop->currentPath->links[i+1].second->route_pointer;
            unsigned int minutes = tempStop->currentPath->links[i].second->start_hours;
            unsigned int hours = tempStop->currentPath->links[i].second->start_minutes;
            while(tempRouteP->stops.size() > l){
                if(tempStop->currentPath->links[i].first->stop_id
                        ==
                        tempRouteP->stops[l].first->stop_id){
                    minutes = minutes + tempRouteP->stops[l].second;
                    l = tempRouteP->stops.size();
                }
                l++;
            }
            while(minutes > 60){
                hours++;
                minutes = minutes - 60;
            }
            cout << hours << ":"
                 <<  minutes << " "
                 << tempStopID << ", "
                 <<  tempStopName << endl;
            bus2ID = bus1ID;
        }
    }

}

void Datastructure::findPath(stop* startStop, int endStop, unsigned int hours, unsigned int minutes, pathtoStop* path){
    size_t i = 0;
    //Tarkistetaan, onko pysakilla kayty. Jos nykyinen reitti on parempi, tarkistetaan pysakilta lahtevat reitit.
    if(startStop->currentPath == NULL){
        startStop->currentPath = path;
    }
    else if(startStop->currentPath->hours >= path->hours){
        if (startStop->currentPath->minutes > path->minutes || startStop->currentPath->hours > path->hours){
            startStop->currentPath = path;
        }
        else{
            return;
        }
    }
    else{
        return;
    }
    //Jos ollaan paatepysakilla, ohitetaan uuden reitin etsiminen.
    if(startStop->stop_id == endStop){
        return;
    }
    //Jos pysakki on uusi tai uusi reitti on parempi, tarkistetaan uusien reittien nopeus.
    //Ensin etsitaan lahtoajan jalkeen lahtevat bussit.
    while(startStop->buses.size() > i){
        //Tarkistetaan, lahteeko bussi aloitusajan jalkeen
        if(startStop->buses[i].second.first >= hours){
            if (startStop->buses[i].second.second >= minutes){
                size_t j = 0;
                bus* tempBus = startStop->buses[i].first;

                bool start = false;
                while(j < tempBus->route_pointer->stops.size()){
                    //Etsitaan aloituspysakki reitilta.
                    pair<stop*, unsigned int> tempStop = tempBus->route_pointer->stops[j];
                    if(start == false && startStop->stop_id == tempStop.first->stop_id){
                        start = true;
                    }
                    else if(start == false){

                    }
                    else{
                        //Aloituspysakin jalkeen tarkastetaan loput reitin pysakit.
                        unsigned int tempHours = tempBus->start_hours;
                        unsigned int tempMinutes = tempBus->start_minutes;
                        tempMinutes = tempMinutes + tempStop.second;
                        while(tempMinutes >= 60){
                            tempMinutes = tempMinutes -60;
                            tempHours++;
                        }
                        pathtoStop* tempPath = new pathtoStop;
                        vector<pair<stop*, bus*>> templinkVect;
                        for(size_t i = 0; i < path->links.size(); i++){
                            templinkVect.push_back(path->links[i]);
                        }
                        pair<stop*, bus*> tempPair = make_pair(startStop,tempBus);
                        templinkVect.push_back(tempPair);
                        tempPath->links = templinkVect;
                        tempPath->hours = tempHours;
                        tempPath->minutes = tempMinutes;
                        findPath(tempBus->route_pointer->stops[j].first, endStop, tempHours, tempMinutes, tempPath);
                    }
                    j++;
                }
            }
            else{

            }
        }
        else{

        }
        i++;
    }
}

/*
path1 *Datastructure::findPath(stop* startStop, int endStop, unsigned int hours, unsigned int minutes, int etaisyys)
=======

Datastructure::path1 *Datastructure::findPath(Datastructure::stop *startStop, int endStop, unsigned int hours, unsigned int minutes, int etaisyys)
>>>>>>> e767fd1f2f3f2c7ea7c1566b9952ee29a504f92c
{

    visitedPointers.push_back(startStop);
    int tempEtaisyys = etaisyys + 1;
    path1* tempPath = new path1;
    tempPath->etaisyys = tempEtaisyys;
    size_t i = 0;
    vector<path1*> mahdolliset_reitit;
    //Kaydaan lapi kaikki pysakilta lahtevat bussit.
    while(startStop->buses.size() > i)
    {
        //Tarkistetaan, lahteeko bussi lahtoajan jalkeen
        if(startStop->buses[i].second.first >= hours)
        {
            if(startStop->buses[i].second.second >= minutes)
            {

                bus* tempBus = startStop->buses[i].first;
                size_t j = 0;
                //Tarkistetaan kaikki bussin pysakit
                bool jalkeen;
                while(tempBus->route_pointer->stops.size() > j){
                    stop* tempStop = tempBus->route_pointer->stops[j].first;
                    //Tarkistetaan, onko pysakki alkuperaisen lahtopysakin jalkeen.
                    if(tempStop->stop_id == startStop->stop_id)
                    {
                        jalkeen = true;
                    }
                    else
                    {
                        if(jalkeen)
                        {
                            //Tarkistetaan, onko pysakki lopullinen paamaara.
                            if(tempStop->stop_id == endStop)
                            {
                                tempPath->pathStop = tempStop;
                                tempPath->bus1 = tempBus;
                                tempPath->etaisyys = tempEtaisyys;
                                tempPath->hours = startStop->buses[i].second.first;
                                tempPath->minutes = startStop->buses[i].second.second;
                                tempPath->next = NULL;
                                return tempPath;
                            }
                            else
                            {
                                //Tarkistetaan, onko pysakilla jo kayty.
                                size_t k = 0;
                                bool visited = false;
                                while(k < visitedPointers.size())
                                {
                                    if(tempStop->stop_id == visitedPointers[k]->stop_id)
                                    {
                                        visited = true;
                                        k = visitedPointers.size();
                                    }
                                    else
                                    {
                                        k++;
                                    }
                                }
                                //Jos pysakilla ei ole kayty, aloitetaan sen tutkiminen.
                                if(visited == false)
                                {
                                    path1* tempPath4 = findPath(tempStop, endStop, hours, minutes, tempEtaisyys);
                                    //Jos loydetaan reitti paatepysakille, lisataan se mahdollisiin reitteihin.
                                    if(tempPath4 != NULL){
                                        mahdolliset_reitit.push_back(tempPath4);
                                    }
                                    else
                                    {

                                    }
                                }
                                else
                                {

                                }
                            }
                        }
                        else
                        {

                        }
                    }
                    j++;
                }

            }
            else
            {

            }
        }
        else
        {

        }
        i++;
    }
    path1* tempPath2 = NULL;

    size_t l = 0;
    //Etsitaan lyhin reitti.
    while(l < mahdolliset_reitit.size())
    {
        int etaisyys;
        path1* tempPath3 = mahdolliset_reitit[l];
        //Mitataan etaisyys lahtopisteesta.
        while(tempPath3->next != NULL){
            etaisyys++;
            tempPath3 = tempPath3->next;
        }
        mahdolliset_reitit[l]->etaisyys = etaisyys;
        //Jos on ensimmainen tutkittu reitti, lisataan se.
        if(tempPath2 == NULL)
        {
            tempPath2 = tempPath3;
        }
        //Jos reitti on lyhyempi, kuin aikaisempi, vaihdetaan se lyhimmaksi reitiksi.
        else if(tempPath2->etaisyys > mahdolliset_reitit[l]->etaisyys)
        {
            tempPath2 = mahdolliset_reitit[l];
        }
        else
        {

        }
        l++;
    }
    //Jos yhtaan reittia ei ole tallennettu, ollaan jouduttu umpikujaan.
    if(tempPath2 == NULL)
    {
        return NULL;
    }
    //Muuten palautetaan uusi loydetty reitti.
    else
    {
        tempPath->bus1 = tempPath2->edellinen_Bussi;
        tempPath->next = tempPath2;
        return tempPath;
    }
}
//*/
