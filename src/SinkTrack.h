#ifndef SINKTRACK_H
#define SINKTRACK_H

#include "Track.h"

class SinkTrack: public Track {
private:
public:
    SinkTrack(int lenght, int velocity);
    
    virtual ~SinkTrack();
    
    void waitingSemaphore();
    
    void semaphoreUnblock(int evtTime);
    
    void semaphoreBlock(int evtTime);
    
    bool semaphoreBlocked();
    
    virtual void outgoing(int evtTime);
};
#endif
