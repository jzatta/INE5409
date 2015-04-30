

public abstract class Track {
 private:
    Queue<Vehicle> *cars;
    int totalLenght, usedLenght, velocity;
 public:
    Track(int lenght, int velocity){
        this->lenght = lenght;
        this->velocity = velocit;
        this->usedLengt = 0;
        cars = new Queue<Vehicle>();
    }

    Event *addCar(Vehicle *car) {
        if ((totalLenght - usedLenght) >= car->getLenght()) {
            cars->add(car);
            //need to calculate time when the car is ready to go and generateEvent();
            return generateEvent();
        }
        return NULL;
    }

    Vehicle *removeCar() {
        return cars->remove();
    }
    Event *generateEvent(/*Event Configurations*/);
}
