#include "Transport.h"

Truck::Truck(int id) {
    ID = id;
    TOTAL_COST = 0;
    TOTAL_INCOME = 0;
}

double Truck::cost(int targetDistance, int weight) {
    return 0;
}

double Truck::price(int targetDistance) {
    return 0;
}

void Truck::transport(int targetDistance, int weight) {
}

double Truck::getTotalCost() const {
    return TOTAL_COST;
}

double Truck::getTotalIncome() const {
    return TOTAL_INCOME;
}

int Truck::getID()const {
    return ID;
}

NormalTruck::NormalTruck(int id, int maxDistance) : Truck(id) {
    MAX = maxDistance;
}

double NormalTruck::cost(int targetDistance, int weight) {
    if (targetDistance > MAX)
        return -1;
    else {
        double cost = (double)weight * (double)targetDistance;
        return cost;
    }
}

double NormalTruck::price(int targetDistance) {
    if (targetDistance > MAX)
        return -1;
    else {
        double price = (double)targetDistance * 5.0;
        if (price < 100)
            price = 100;
        return price;
    }
}

void NormalTruck::transport(int targetDistance, int weight) {
    if (cost(targetDistance, weight) != -1) {
        TOTAL_COST += cost(targetDistance, weight);
        TOTAL_INCOME += price(targetDistance);
    }
}

AdvancedTruck::AdvancedTruck(int id) : NormalTruck(id, 100000) {
}

double AdvancedTruck::cost(int targetDistance, int weight) {
    double cost = 50.0 + (double)weight * (double)targetDistance;
    return cost;
}

double AdvancedTruck::price(int targetDistance) {
    double price = (double)targetDistance * 8.0;
    if (price < 150)
        price = 150;
    return price;
}

LongDistanceTruck::LongDistanceTruck(int id) : AdvancedTruck(id) {
}

double LongDistanceTruck::price(int targetDistance) {
    double price = AdvancedTruck::price(targetDistance);
    if (targetDistance < 30)
        price *= 1.1;
    else
        price *= 0.9;
    return price;
}