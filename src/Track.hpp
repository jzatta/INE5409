#ifndef TRACK_HPP
#define TRACK_HPP

#include <cstdlib>
#include "Eventable.hpp"
#include "Event.hpp"
#include "List.hpp"
#include "Manager.hpp"
#include "Queue.hpp"
#include "Vehicle.hpp"

class Track: public Eventable {
protected:
    Queue<Vehicle> *cars;
    List<Track> *targetTracks;
    List<int> *targetProbability;
    bool trackBlocked;
    int trafficJam;
    int totalLenght, usedLenght, velocity; // All saved in SI
    List<Track> *waitingTracks;
public:
    Track(int lenght, int velocity){
        this->totalLenght = lenght;
        this->velocity = (int)((double)velocity / 3.6);
        this->usedLenght = 0;
        trackBlocked = false;
        trafficJam = 0;
        cars = new Queue<Vehicle>();
        targetTracks = new List<Track>();
        targetProbability = new List<int>();
        waitingTracks = new List<Track>();
    }
    
    virtual ~Track() {
        while (!cars->empty())
            delete cars->remove();
        while (!targetProbability->empty())
            delete targetProbability->remove(0);
        delete cars;
        delete targetTracks;
        delete targetProbability;
        delete waitingTracks;
    }
    
    void addTargetTracks(Track *track, int prob) {
        targetTracks->add(track,0);
        /* Ignorar */
        targetProbability->add(new int(prob),0);
        /* Gambiarra pra nao precisar mudar as listas */
    }

    bool Event *incoming(Vehicle *car) {
        if ((totalLenght - usedLenght) >= car->getLenght()) {
            cars->add(car);
            car->setupDir(-1);
            usedLenght += car->getLenght();
            int timeToGetOut = ( totalLenght - car->getLenght() ) / velocity;
            generateEvent(timeToGetOut);
            return true;
        }
        return false;
    }

    virtual void outgoing(int evtTime) {
        if (trackBlocked){
            trafficJam++;
            return;
        }
        // threat semaphore if open continue, else block track and add to semaphore notify
        if (semaphoreBlocked()) {
            waitingSemaphore();
            return;
        }
        Vehicle *car = cars->get();
        int destination = car->getDirection();
        if (destination == -1) {
            int totalChances = 0, i;
            for (i = 0; !targetProbability->empty(); i++) {
                totalChances += targetProbability->get(i);
            }
            totalChances = std::rand() % totalChances;
            for (i = 0; totalChances >= 0; i++) {
                totalChances -= targetProbability->get(i);
            }
            destination = i;
            car->setupDir(destination);
        }
        bool test = targetTracks->get(destination)->incoming(car);
        if (test) {
            cars->remove();
            usedLenght -= car->getLenght();
            if (trafficJam--) {
                int timeToGetOut = car->getLenght() / velocity;
                generateEvent(evtTime + timeToGetOut);
            }
            while (!waitingTracks->empty())
                waitingTracks->remove()->notify(evtTime);
            return;
        }
        trackBlocked = true;
        targetTracks->get(destination)->waitingFor(this);
    }
    
    void notify(int evtTime) {
        trackBlocked = false;
        outgoing(evtTime);
    }
    
    void waitingFor(Track *t) {
        waitingTracks->add(t);
    }
    
    void *generateEvent(int time) {
        Event* evt = new Event(this, &outgoing,  time);
        Manager::getEvents()->add(evt);
    }
    
    void waitingSemaphore();
    void semaphoreUnblock();
    void semaphoreBlock();
    bool semaphoreBlocked();
};
#endif
