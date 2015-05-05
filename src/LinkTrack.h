#ifndef LINKTRACK_H
#define LINKTRACK_H

#include "Track.hpp"

class LinkTrack: public Track {
private:
    bool semaphoreRed, carWaitingSemaphore;
public:
    LinkTrack(int lenght, int velocity);
    
    virtual ~LinkTrack();
    
    void waitingSemaphore();
    
    void semaphoreUnblock(int evtTime);
    
    void semaphoreBlock(int evtTime);
    
    bool semaphoreBlocked();
};
#endif
