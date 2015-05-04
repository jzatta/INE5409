

class SourceTrack: public Track {
private:
    int timeGenerate;
public:
    SourceTrack(int lenght, int velocity, int time): Track(int lenght, int velocity) {
        timeGenerate = time;
    }
    
    virtual ~SourceTrack() {}
    
    void createCar(Event *evt) {
        Vehicle *car;
        Event* newEvt = new Event(this, evt->getTime() + timeGenerate)
        Manager::getEvents()->add(newEvt);
        car = new Vehicle(Vehicle::randomSize());
        if (incoming(car))
            return;
        delete car;
    }
}