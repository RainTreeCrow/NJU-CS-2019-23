#include <iostream>
#include <string>
using namespace std;

class CarRecord {
    string car_c;
    int date_c;
public:
    int time_h;
    int time_m;
    CarRecord();
    void set(string car, int date, string time);
    string getCar();
    int getDate();
    string getTime();
};
