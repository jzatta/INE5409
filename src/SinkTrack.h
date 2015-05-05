#ifndef SINKTRACK_HPP
#define SINKTRACK_HPP

#include "Track.hpp"
#include "Vehicle.hpp"

class SinkTrack: public Track {
private:
public:
    SinkTrack(int lenght, int velocity): Track(int lenght, int velocity);
    
    virtual ~SinkTrack();
    
    void waitingSemaphore();
    
    void semaphoreUnblock(int evtTime);
    
    void semaphoreBlock(int evtTime);
    
    bool semaphoreBlocked();
    
    virtual void outgoing(int evtTime);
};
#endif
