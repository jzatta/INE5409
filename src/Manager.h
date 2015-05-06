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
    SourceWE = 0,
    SourceEW = 1,
    SourceNS1 = 2,
    SourceNS2 = 3,
    SourceSN1 = 4,
    SourceSN2 = 5,
    LinkWE = 6,
    LinkEW = 7,
    SinkWE = 8,
    SinkEW = 9,
    SinkNS1 = 10,
    SinkNS2 = 11,
    SinkSN1 = 12,
    SinkSN2 = 13
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
