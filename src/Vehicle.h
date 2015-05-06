#ifndef VEHICLE_H
#define VEHICLE_H

class Vehicle {
private:
    int size;
    int direction;
public:
    Vehicle(int _size);
    ~Vehicle();
    static int ramdomSize();
    int getLenght();
    int getDirection();
    void setupDir(int dir);
};
#endif
