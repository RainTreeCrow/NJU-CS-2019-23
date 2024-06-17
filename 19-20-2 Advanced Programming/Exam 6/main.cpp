#include <iostream>
#include <vector>
#include "CarDatabase.h"
using namespace std;

int main(int argc, char** argv) {
    CarRecord cr;
    cr.set("A9999",1,"16:33");
    CarDatabase cd("database"),cd2("database");
    cd.add(cr);
    cd2.read();
    vector<CarRecord>::iterator it;
    for (it = cd2.record.begin(); it != cd2.record.end(); it++)
        cout << it->getCar() << "," << it->getDate() <<","<< it->getTime() << endl;
    
    cd.del("A9999");
	return 0;
}