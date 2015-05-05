#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <cstdlib>
#include "Eventable.hpp"
#include "Event.hpp"
#include "LinkTrack.hpp"
#include "List.hpp"
#include "Manager.hpp"
#include "Queue.hpp"
#include "Semaphores.hpp"
#include "SinkTrack.hpp"
#include "SortedList.hpp"
#include "SourceTrack.hpp"
#include "Track.hpp"
#include "Vehicle.hpp"


/*       North
 *         /\
 *  West  <-->  East
 *         \/
 *       South
 */

#define WE_TRACKS 3
#define EW_TRACKS 3
#define NS_TRACKS 4
#define SN_TRACKS 4


class Manager {
private:
    List<Track> *tracks;
    int simulationTime;
    static SortedList<Event> *events;
    static Semaphores *semaphores;
    static int createdCars, destroyedCars;
    enum tracks {
        SourceWE,
        SourceEW,
        SourceNS1,
        SourceNS2,
        SourceSN1,
        SourceSN2,
        LinkWE,
        LinkEW,
        SinkWE,
        SinkEW,
        SinkNS1,
        SinkNS2,
        SinkSN1,
        SinkSN2
    };
public:
    Manager(int semaphoreOpenedTime, int _simulationTime);
    
    int manage();
    
    static SortedList<Event> *getEvents();
    
    static Semaphores *getSemaphores();
    
    static void addCreatedCar();
    
    static void addDestroyedCars();
    
};

#endif
