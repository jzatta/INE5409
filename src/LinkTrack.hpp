
#include "Track.hpp"

class LinkTrack: public Track {
private:
    bool semaphoreRed, carWaitingSemaphore;
public:
    LinkTrack(int lenght, int velocity): Track(int lenght, int velocity) {
        semaphoreRed = true;
        carWaitingSemaphore = false;
    }
    
    virtual ~LinkTrack() {}
    
    void waitingSemaphore() {
        carWaitingSemaphore = true;
    }
    
    void semaphoreUnblock(int evtTime) {
        semaphoreRed = false;
        if (carWaitingSemaphore){
            carWaitingSemaphore = false;
            outgoing(evtTime);
        }
    }
    
    void semaphoreBlock(int evtTime) {
        semaphoreRed = true;
    }
    
    bool semaphoreBlocked() {
        return semaphoreRed;
    }
};
