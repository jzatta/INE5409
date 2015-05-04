

class Track: public Eventable  {
protected:
    Queue<Vehicle> *cars;
    List<Track> *targetTracks;
    List<int> *targetProbability;
    bool trackBlocked;
    int totalLenght, usedLenght, velocity;
    List<Track> *unblockTracks;
public:
    Track(int lenght, int velocity){
        this->totalLenght = lenght;
        this->velocity = velocity;
        this->usedLenght = 0;
        trackBlocked = false;
        cars = new Queue<Vehicle>();
        targetTracks = new List<Track>();
        targetProbability = new List<int>();
        unblockTracks = new List<Track>();
    }
    
    void addTargetTracks(Track *track, int prob) {
        targetTracks->add(track);
        targetProbability->add(prob);
    }
    
    virtual ~Track(){
        delete cars;
        delete targetTracks;
    }

    bool Event *incoming(Vehicle *car) {
        if ((totalLenght - usedLenght) >= car->getLenght()) {
            cars->add(car);
            car->setupDir(-1);
            //need to calculate time when the car is ready to go and generateEvent();
            generateEvent();
            return true;
        }
        return false;
    }

    virtual void outgoing() {
        if (trackBlocked)
            return;
        Vehicle *car = cars->get();
        int destination = car->getDirection();
        if (destination == -1) {
            destination = // Calculate dir based on targetTracks, and probs
            car->setupDir(destination);
        }
        bool test = targetTracks->get(destination)->incoming(car);
        if (test) {
            cars->remove();
            while (!unblockTracks->empty())
                unblockTracks->remove()->notify();
            return;
        }
        trackBlocked = true;
        targetTracks->get(destination)->waitingFor(this);
    }
    
    void notify() {
        trackBlocked = false;
        outgoing();
    }
    
    void waitingFor(Track *t) {
        unblockTracks->add(t);
    }
    
    void *generateEvent(int time) {
        Event* evt = new Event(this, time)
        Manager::getEvents()->add();
    }
}
