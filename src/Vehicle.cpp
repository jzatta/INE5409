#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <cstdlib>
#include "Vehicle.h"

Vehicle::Vehicle(int _size) {
    size = _size + 3; // distance from others vehicles
    direction = -1;
    Manager::addCreatedCar();
}

Vehicle::~Vehicle() {
    Manager::addDestroyedCars();
}

static int Vehicle::ramdomSize() {
    return (std::rand() % 9) + 2;
}

int Vehicle::getLenght() {
    return size;
}

int Vehicle::getDirection() {
    return direction;
}

void Vehicle::setupDir(int dir) {
    direction = dir;
}
