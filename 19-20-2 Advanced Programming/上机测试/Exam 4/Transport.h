#pragma once

class Truck {
protected:
    int ID;
    double TOTAL_COST;
    double TOTAL_INCOME;
public:
    Truck(int id);
    virtual double cost(int targetDistance, int weight);
    virtual double price(int targetDistance);
    virtual void transport(int targetDistance, int weight);
    double getTotalCost() const;
    double getTotalIncome() const;
    int getID()const;
};

class NormalTruck :public Truck {
    int MAX;
public:
    NormalTruck(int id, int maxDistance);
    double cost(int targetDistance, int weight);
    double price(int targetDistance);
    void transport(int targetDistance, int weight);
};

class AdvancedTruck :public NormalTruck {
public:
    AdvancedTruck(int id);
    double cost(int targetDistance, int weight);
    double price(int targetDistance);
};

class LongDistanceTruck :public AdvancedTruck {
public:
    LongDistanceTruck(int id);
    double price(int targetDistance);
};