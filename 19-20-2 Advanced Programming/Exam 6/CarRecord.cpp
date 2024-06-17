#include "CarRecord.h" 

CarRecord::CarRecord() {
    car_c = "00000";
    date_c = 0;
    time_h = 0;
    time_m = 0;
}

void CarRecord::set(string car, int date, string time) {
    car_c = car;
    date_c = date;
    time_h = (time[0] - 48) * 10 + (time[1] - 48);
    time_m = (time[3] - 48) * 10 + (time[4] - 48);
}

string CarRecord::getCar() {
    return car_c;
}

int CarRecord::getDate() {
    return date_c;
}

string CarRecord::getTime() {
    string s = "00:00";
    s[0] = time_h / 10 + 48;
    s[1] = time_h % 10 + 48;
    s[3] = time_m / 10 + 48;
    s[4] = time_m % 10 + 48;
    return s;
}
