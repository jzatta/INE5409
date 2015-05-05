#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <cstdlib>
#include "Manager.hpp"

class Vehicle {
private:
    int size;
    int direction;
public:
    Vehicle(int _size) {
        size = _size + 3; // distance from others vehicles
        direction = -1;
        Manager::addCreatedCar();
    }
    
    ~Vehicle() {
        Manager::addDestroyedCars();
    }
    
    static int ramdomSize() {
        return (std::rand() % 9) + 2;
    }
    
    int getLenght() {
        return size;
    }
    
    int getDirection() {
        return direction;
    }
    
    void setupDir(int dir) {
        direction = dir;
    }
};
#endif
