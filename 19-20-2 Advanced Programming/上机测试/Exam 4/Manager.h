#pragma once
#include "Transport.h"

class Manager {
    Truck* TRUCKS[40];
    int count;
public:
    Manager();
    void addTruck(Truck* t);
    Truck* transport(int targetDistance, int weight);
    double getAllIncome();
    double getAllCost();
};