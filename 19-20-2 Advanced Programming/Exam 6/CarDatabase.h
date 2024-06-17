#include <iostream>
#include <string>
#include <vector>
#include "CarRecord.h" 
using namespace std;

class CarDatabase {
private: 
    std::string file;
public:
	vector<CarRecord> record;
    CarDatabase(string filename);
    
    void read();
    void add(CarRecord cr);
    void del(string car);
    void del(int date);

    void del(string car, int date);

    void del(string car, int date, string time);
    void del(int date, string time_start, string time_end);
    
    vector<CarRecord> IndexRecordsByCar(string car);
    vector<CarRecord> IndexRecordsByDate(int date);
};
