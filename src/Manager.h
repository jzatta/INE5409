#ifndef MANAGER_H
#define MANAGER_H


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

class Event;
class Semaphores;
class Track;

template<typename T>
class List;
template<typename T>
class SortedList;

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
    
class Manager {
private:
    List<Track> *tracks;
    int simulationTime;
    static SortedList<Event> *events;
    static Semaphores *semaphores;
    static int createdCars, destroyedCars;
public:
    Manager(int semaphoreOpenedTime, int _simulationTime);
    
    int manage();
    
    static SortedList<Event> *getEvents();
    
    static Semaphores *getSemaphores();
    
    static void addCreatedCar();
    
    static void addDestroyedCars();
    
};

#endif
