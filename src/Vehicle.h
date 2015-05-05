#ifndef VEHICLE_H
#define VEHICLE_H

#include <cstdlib>
#include "Manager.hpp"

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
