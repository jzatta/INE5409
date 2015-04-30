

class Event {
 private:
    int time;
    Eventable *evt;
 public:
    Event(Eventable *_evt, int _time) {
        evt = _evt;
        time = _time;
    }
    
    int getTime() {
        return time;
    }
    
    void handleEvent() {
        evt->execute();
    }
}
