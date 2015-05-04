

class Track: public Eventable  {
protected:
    Queue<Vehicle> *cars;
    List<Track> *targetTracks;
    int totalLenght, usedLenght, velocity;
public:
    Track(int lenght, int velocity){
        this->totalLenght = lenght;
        this->velocity = velocity;
        this->usedLenght = 0;
        cars = new Queue<Vehicle>();
        targetTracks = new List<Track>();
    }
    
    void addTargetTracks(Track *track) {
        targetTracks->add(track);
    }
    
    virtual ~Track(){
        delete cars;
        delete targetTracks;
    }

    bool Event *incoming(Vehicle *car) {
        if ((totalLenght - usedLenght) >= car->getLenght()) {
            cars->add(car);
            //need to calculate time when the car is ready to go and generateEvent();
            generateEvent();
            return true;
        }
        return false;
    }

    virtual void outgoing() {
        int destination = cars
        bool test = 
    }
    
    void *generateEvent(int time) {
        Event* evt = new Event(this, time)
        Manager::getEvents()->add();
    }
}
