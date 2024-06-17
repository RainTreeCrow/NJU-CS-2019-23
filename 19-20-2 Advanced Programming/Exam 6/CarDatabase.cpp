#include "CarDatabase.h"
#include <fstream>
#include <algorithm>

bool compareByDate(CarRecord a, CarRecord b) {
    int time_a = a.time_h * 60 + a.time_m;
    int time_b = b.time_h * 60 + b.time_m;
    if (time_a < time_b)
        return true;
    else if (time_a > time_b)
        return false;
    else
        return a.getCar() < b.getCar();
}

bool compareByCar(CarRecord a, CarRecord b) {
    if (a.getDate() < b.getDate())
        return true;
    else if (a.getDate() > b.getDate())
        return false;
    else {
        int time_a = a.time_h * 60 + a.time_m;
        int time_b = b.time_h * 60 + b.time_m;
        return time_a < time_b;
    }
}

//------------------------------------------------------------------------------------ 

CarDatabase::CarDatabase(std::string filename) {
    file = filename;
}

void CarDatabase::read() {
    record.clear();
    ifstream in;
    string temp_car, temp_time;
    int temp_date;
    in.open(file.c_str());
    while (!in.eof()) {
        CarRecord temp;
        in >> temp_car >> temp_date >> temp_time;
        temp.set(temp_car, temp_date, temp_time);
        record.push_back(temp);
        in.get();
        if (in.peek() == '\n')
            break;
    }
    in.close();
}

void CarDatabase::add(CarRecord cr) {
    bool exist = false;
    vector<CarRecord>::iterator it;
    for (it = record.begin(); it != record.end(); it++) {
        if (it->getCar() == cr.getCar() && it->getDate() == cr.getDate()
            && it->getTime() == cr.getTime()) {
            exist = true;
            break;
        }
    }
    if (!exist) {
        record.push_back(cr);
        ofstream out;
        out.open(file.c_str(), ios::app);
        out << cr.getCar() << ' ' << cr.getDate() << ' ' << cr.getTime() << endl;
        out.close();
    }
}

void CarDatabase::del(string car) {
    vector<CarRecord>::iterator it;
    //清空文件 
    ofstream clr;
    clr.open(file.c_str(),ios::out | ios::trunc);
    clr.close();
    
//    for (it = record.begin(); it != record.end();) {
//        if (it->getCar() == car)
//            it = record.erase(it);
//        else {
//            out << it->getCar() << ' ' << it->getDate() << ' ' << it->getTime() << endl;
//            ++it;
//        }
//    }

	//删除记录 
	for (it = record.begin(); it != record.end();) {
		if (it->getCar() == car)
			it = record.erase(it);
		else
			++it;			
	}
	
	//同步文件 
	ofstream wrt;
    wrt.open(file.c_str(), ios::app);
	for (it = record.begin(); it != record.end(); it++) {
        wrt << it->getCar() << ' ' << it->getDate() << ' ' << it->getTime() << endl;
	} 
	wrt.close();
}

void CarDatabase::del(int date) {
    vector<CarRecord>::iterator it;
    
    //清空文件
    ofstream clr;
    clr.open(file.c_str(),ios::out | ios::trunc);
    clr.close();
    
//    for (it = record.begin(); it != record.end();) {
//        if (it->getDate() == date)
//            it = record.erase(it);
//        else {
//            out << it->getCar() << ' ' << it->getDate() << ' ' << it->getTime() << endl;
//            ++it;
//        }
//    }
//    out.close();

	//删除记录 
    for (it = record.begin(); it != record.end();) {
        if (it->getDate() == date)
            it = record.erase(it);
        else {
            ++it;
        }
    }	

	//同步文件 
	ofstream wrt;
    wrt.open(file.c_str(), ios::app);
	for (it = record.begin(); it != record.end(); it++) {
        wrt << it->getCar() << ' ' << it->getDate() << ' ' << it->getTime() << endl;
	} 
	wrt.close();
}

void CarDatabase::del(string car, int date) {
    vector<CarRecord>::iterator it;

	//清空文件 
    ofstream clr;
    clr.open(file.c_str(),ios::out | ios::trunc);
    clr.close();

	//删除记录 
    for (it = record.begin(); it != record.end();) {
        if (it->getCar() == car && it->getDate() == date)
            it = record.erase(it);
        else {
            ++it;
        }
    }

	//同步文件 
	ofstream wrt;
    wrt.open(file.c_str(), ios::app);
	for (it = record.begin(); it != record.end(); it++) {
        wrt << it->getCar() << ' ' << it->getDate() << ' ' << it->getTime() << endl;
	} 
	wrt.close();
}

void CarDatabase::del(string car, int date, string time) {
    vector<CarRecord>::iterator it;
	//清空文件 
    ofstream clr;
    clr.open(file.c_str(),ios::out | ios::trunc);
    clr.close();

	//删除记录 
    for (it = record.begin(); it != record.end();) {
        if (it->getCar() == car && it->getDate() == date && it->getTime() == time)
            it = record.erase(it);
        else {
            //out << it->getCar() << ' ' << it->getDate() << ' ' << it->getTime() << endl;
            ++it;
        }
    }

	//同步文件 
	ofstream wrt;
    wrt.open(file.c_str(), ios::app);
	for (it = record.begin(); it != record.end(); it++) {
        wrt << it->getCar() << ' ' << it->getDate() << ' ' << it->getTime() << endl;
	} 
	wrt.close();
}

void CarDatabase::del(int date, string time_start, string time_end) {
    vector<CarRecord>::iterator it;

    int start = (time_start[0] - 48) * 600 + (time_start[1] - 48) * 60
        + (time_start[3] - 48) * 10 + (time_start[4] - 48);
    int end = (time_end[0] - 48) * 600 + (time_end[1] - 48) * 60
        + (time_end[3] - 48) * 10 + (time_end[4] - 48);
        
	//清空文件 
    ofstream clr;
    clr.open(file.c_str(),ios::out | ios::trunc);
    clr.close();    
        
        
    for (it = record.begin(); it != record.end();) {
        if (it->getDate() == date) {
            int time = it->time_h * 60 + it->time_m;
            if (start <= time && end >= time)
                it = record.erase(it);
        }
        else {
            //out << it->getCar() << ' ' << it->getDate() << ' ' << it->getTime() << endl;
            ++it;
        }
    }

    //同步文件 
	ofstream wrt;
    wrt.open(file.c_str(), ios::app);
	for (it = record.begin(); it != record.end(); it++) {
        wrt << it->getCar() << ' ' << it->getDate() << ' ' << it->getTime() << endl;
	} 
	wrt.close();
}

vector<CarRecord> CarDatabase::IndexRecordsByCar(string car) {
    vector<CarRecord> cars;
    vector<CarRecord>::iterator it;
    for (it = record.begin(); it != record.end(); it++) {
        if (it->getCar() == car) {
            CarRecord temp;
            temp.set(it->getCar(), it->getDate(), it->getTime());
            cars.push_back(temp);
        }
    }
    sort(cars.begin(), cars.end(), compareByCar);
    return cars;
}

vector<CarRecord> CarDatabase::IndexRecordsByDate(int date) {
    vector<CarRecord> cars;
    vector<CarRecord>::iterator it;
    for (it = record.begin(); it != record.end(); it++) {
        if (it->getDate() == date) {
            vector<CarRecord>::iterator it2;
            bool exist = false;
            for (it2 = cars.begin(); it2 != cars.end(); it2++) {
                if (it->getCar() == it2->getCar()) {
                    exist = true;
                    int time = it->time_h * 60 + it->time_m;
                    int time2 = it2->time_h * 60 + it2->time_m;
                    if (time > time2) {
                        it2->time_h = it->time_h;
                        it2->time_m = it->time_m;
                    }
                    break;
                }
            }
            if (!exist) {
                CarRecord temp;
                temp.set(it->getCar(), it->getDate(), it->getTime());
                cars.push_back(temp);
            }
        }
    }
    sort(cars.begin(), cars.end(), compareByDate);
    return cars;
}

