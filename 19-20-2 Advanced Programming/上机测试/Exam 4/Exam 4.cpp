#include <iostream>
#include"Transport.h"
#include"Transport.cpp"
#include"Manager.h"
#include"Manager.cpp"
using namespace std;

int main()
{
    Manager MAN = Manager();
    NormalTruck* a = new NormalTruck(100, 10);
    AdvancedTruck* b = new AdvancedTruck(101);
    LongDistanceTruck* c = new LongDistanceTruck(102);
    MAN.addTruck(a);
    MAN.addTruck(b);
    MAN.addTruck(c);
    Truck* t = MAN.transport(10, 10);
    cout << MAN.getAllCost() << ' ' << MAN.getAllIncome() << endl;
    return 0;
}