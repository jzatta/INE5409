

public abstract class Track: public Eventable {
 private:
 public:
    bool addCar(Car *car);
    void removeCar(Car *car);
    bool hasSpace(int carSize);
}
