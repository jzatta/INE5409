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
    Manager(int semaphoreOpenedTime, int _simulationTime) {
        createdCars = destroyedCars = 0;
        simulationTime = _simulationTime;
        tracks = new List<Track>();
        events = new SortedList<Event>();
        semaphores = new Semaphores(semaphoreOpenedTime);
    }
    
    int manage(){
        int i;
        Event *runningEvt;
        Track *trackPointer;
        // creation of tracks
            // SourceTrack
                // WE
        trackPointer = new SourceTrack(2000, 80, 10, 2);
        tracks->add(trackPointer,SourceWE);
                // EW
        trackPointer = new SourceTrack(400,  30, 10, 2);
        tracks->add(trackPointer,SourceEW);
                // NS
        trackPointer = new SourceTrack(500, 60, 20, 5);
        tracks->add(trackPointer,SourceNS1);
        trackPointer = new SourceTrack(500, 40, 20, 5);
        tracks->add(trackPointer,SourceNS2);
                // SN
        trackPointer = new SourceTrack(500, 60, 30, 7);
        tracks->add(trackPointer,SourceSN1);
        trackPointer = new SourceTrack(500, 40, 60, 15);
        tracks->add(trackPointer,SourceSN2);
            // LinkTrack
                // WE
        trackPointer = new LinkTrack(300, 60);
        tracks->add(trackPointer,LinkWE);
                // EW
        trackPointer = new LinkTrack(300, 60);
        tracks->add(trackPointer,LinkEW);
            // SinkTrack
                // WE
        trackPointer = new SinkTrack(400, 30);
        tracks->add(trackPointer,SinkWE);
                // EW
        trackPointer = new SinkTrack(2000, 80);
        tracks->add(trackPointer,SinkEW);
                // NS
        trackPointer = new SinkTrack(500, 60);
        tracks->add(trackPointer,SinkNS1);
        trackPointer = new SinkTrack(500, 40);
        tracks->add(trackPointer,SinkNS2);
                // SN
        trackPointer = new SinkTrack(500, 60);
        tracks->add(trackPointer,SinkSN1);
        trackPointer = new SinkTrack(500, 40);
        tracks->add(trackPointer,SinkSN2);
        // linking Tracks and configure semaphores
            // Source WE
        tracks->get(SourceWE)->addTargetTracks(tracks->get(LinkWE),8);
        tracks->get(SourceWE)->addTargetTracks(tracks->get(SinkNS1),1);
        tracks->get(SourceWE)->addTargetTracks(tracks->get(SinkSN1),1);
        semaphores->addTrack(tracks->get(SourceWE),DIRWE);
            // Source NS1
        tracks->get(SourceNS1)->addTargetTracks(tracks->get(LinkWE),8);
        tracks->get(SourceNS1)->addTargetTracks(tracks->get(SinkEW),1);
        tracks->get(SourceNS1)->addTargetTracks(tracks->get(SinkNS1),1);
        semaphores->addTrack(tracks->get(SourceNS1),DIRNS);
            // Source SN1
        tracks->get(SourceSN1)->addTargetTracks(tracks->get(LinkWE),8);
        tracks->get(SourceSN1)->addTargetTracks(tracks->get(SinkSN1),1);
        tracks->get(SourceSN1)->addTargetTracks(tracks->get(SinkEW),1);
        semaphores->addTrack(tracks->get(SourceSN1),DIRSN);
            // Link EW
        tracks->get(LinkEW)->addTargetTracks(tracks->get(SinkEW),4);
        tracks->get(LinkEW)->addTargetTracks(tracks->get(SinkNS1),3);
        tracks->get(LinkEW)->addTargetTracks(tracks->get(SinkSN1),3);
        semaphores->addTrack(tracks->get(LinkEW),DIREW);
            // Link WE
        tracks->get(LinkWE)->addTargetTracks(tracks->get(SinkWE),4);
        tracks->get(LinkWE)->addTargetTracks(tracks->get(SinkNS2),3);
        tracks->get(LinkWE)->addTargetTracks(tracks->get(SinkSN2),3);
        semaphores->addTrack(tracks->get(LinkWE),DIRWE);
            // Source NS2
        tracks->get(SourceNS2)->addTargetTracks(tracks->get(SinkWE),4);
        tracks->get(SourceNS2)->addTargetTracks(tracks->get(LinkEW),3);
        tracks->get(SourceNS2)->addTargetTracks(tracks->get(SinkSN2),3);
        semaphores->addTrack(tracks->get(SourceNS2),DIRNS);
            // Source SN2
        tracks->get(SourceSN2)->addTargetTracks(tracks->get(SinkWE),4);
        tracks->get(SourceSN2)->addTargetTracks(tracks->get(LinkEW),3);
        tracks->get(SourceSN2)->addTargetTracks(tracks->get(SinkNS2),3);
        semaphores->addTrack(tracks->get(SourceSN2),DIRSN);
            // Source EW
        tracks->get(SourceEW)->addTargetTracks(tracks->get(LinkEW),3);
        tracks->get(SourceEW)->addTargetTracks(tracks->get(SinkNS2),3);
        tracks->get(SourceEW)->addTargetTracks(tracks->get(SinkSN2),4);
        semaphores->addTrack(tracks->get(SourceEW),DIREW);
        while (true) {
            if (events->empty())
                return -1;
            runningEvt = events->remove(0);
            if (runningEvt->getTime > simulationTime) {
                break;
            }
            runningEvt->handleEvent(); // Event suicide here runningEvt == NULL
        }
        
        // print simulation status
        delete events;
        delete semaphores;
        return 0;
    }
    
    static SortedList<Event> *getEvents() {
        return events;
    }
    
    static Semaphores *getSemaphores() {
        return semaphores;
    }
    
    static void addCreatedCar() {
        createdCars++;
    }
    
    static void addDestroyedCars() {
        destroyedCars++;
    }
};

int main(int argc, char **argv) {
    // manipulate args
    std::srand(new int[0]);
    // other 'off simulation' initializations
    return new Manager()->manage();
}

#endif
