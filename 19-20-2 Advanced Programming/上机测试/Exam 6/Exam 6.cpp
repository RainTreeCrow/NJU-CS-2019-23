#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "CarRecord.h"
using namespace std;

int main()
{
    CarRecord cr;
    cr.set("A9999",1,"16:33");
    CarDatabase cd("database"),cd2("database");
    //cd.add(cr);
    cd2.read();
    vector<CarRecord>::iterator it;
    for (it = cd2.record.begin(); it != cd2.record.end(); it++)
        cout << it->getCar() << endl;
    return 0;
}