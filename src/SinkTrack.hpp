
#include "Track.hpp"

class SinkTrack: public Track {
private:
public:
    LinkTrack(int lenght, int velocity): Track(int lenght, int velocity) {}
    
    virtual ~SourceTrack() {}
    
    void waitingSemaphore() {}
    
    void semaphoreUnblock(int evtTime) {}
    
    void semaphoreBlock(int evtTime) {}
    
    bool semaphoreBlocked() {
        return false;
    }
    
    virtual void outgoing(int evtTime) {
        Vehicle *car = cars->get();
        
        
        usedLenght -= car->getLenght();
        while (!waitingTracks->empty())
            waitingTracks->remove()->notify(evtTime);
        delete cars->remove();
        return;
    }
}