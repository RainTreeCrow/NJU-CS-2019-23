#include "Manager.h"

Manager::Manager() {
    count = 0;
}

void Manager::addTruck(Truck* t) {
    TRUCKS[count] = t;
    count += 1;
}

Truck* Manager::transport(int targetDistance, int weight) {
    double min_price = 100000000;
    double min_income = 100000000;
    int min_index = 0;
    int min_id = 100000000;
    for (int i = 0; i < count; i++) {
        if (TRUCKS[i]->cost(targetDistance, weight) == -1)
            continue;
        else if (TRUCKS[i]->price(targetDistance) < min_price) {
            min_price = TRUCKS[i]->price(targetDistance);
            min_index = i;
        }
        else if (TRUCKS[i]->price(targetDistance) == min_price) {
            if (TRUCKS[i]->getTotalIncome() < min_income) {
                min_income = TRUCKS[i]->getTotalIncome();
                min_index = i;
            }
            else if (TRUCKS[i]->getTotalIncome() == min_income) {
                if (TRUCKS[i]->getID() < min_id) {
                    min_id = TRUCKS[i]->getID();
                    min_index = i;
                }
            }
        }
    }
    TRUCKS[min_index]->transport(targetDistance, weight);
    return TRUCKS[min_index];
}

double Manager::getAllIncome() {
    double ALL_I = 0.0;
    for (int i = 0; i < count; i++)
        ALL_I += TRUCKS[i]->getTotalIncome();
    return ALL_I;
}

double Manager::getAllCost() {
    double ALL_C = 0.0;
    for (int i = 0; i < count; i++)
        ALL_C += TRUCKS[i]->getTotalCost();
    return ALL_C;
}