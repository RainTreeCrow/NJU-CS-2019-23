#include <iostream>
#include <cstring>
using namespace std;
#pragma warning(disable : 4996)

/*
class Base {
public:
    int bar(char x) {
        return (int)(x);
    }
    virtual int bar(int x) {
        return (2 * x);
    }
};

class Derived : public Base {
public:
    int bar(char x) {
        return (int)(-x);
    }
    int bar(int x) {
        return (x / 2);
    }
};

int main()
{
    Derived Obj;
    Base* pObj = &Obj;
    cout << pObj->bar((char)(100)) << endl;
    cout << pObj->bar(100) << endl;
}
*/

/*
class A {
    int a;
public:
    A() :a(5) {}
    virtual void print()const {
        cout << a << endl;
    }
};

class B : public A {
    char b;
public:
    B() {
        b = 'E';
    }
    void print()const {
        cout << b << endl;
    }
};

void show(A& x) {
    x.print();
}

int main()
{
    A d1, * p;
    B d2;
    p = &d2;
    d1.print();
    d2.print();
    p->print();
    show(d1);
    show(d2);
    return 0;
}
*/

/*
class Animal {
protected:
    char name[10];
    int weight;
    static int total_weight;
    static int count;
public:
    Animal(const char* n, int w = 0) {
        strcpy(name, n);
        weight = w;
        total_weight += weight;
        count += 1;
    }
    virtual void sound() {};
    void show() {
        cout << name << " weights " << weight << " kg." << endl;
    }
    ~Animal() {
        total_weight -= weight;
        count -= 1;
    }
    static int get_total() {
        return total_weight;
    }
    static int get_count() {
        return count;
    }
};

int Animal::total_weight = 0;
int Animal::count = 0;

class Dog :public Animal {
public:
    Dog(const char* n, int w = 0) : Animal(n, w) {}
    void sound() {
        cout << name << ": \"woof woof woof!\"" << endl;
    }
};

class Cat :public Animal {
public:
    Cat(const char* n, int w = 0) : Animal(n, w) {}
    void sound() {
        cout << name << ": \"mew~\"" << endl;
    }
};

class Cow :public Animal {
public:
    Cow(const char* n, int w = 0) : Animal(n, w) {}
    void sound() {
        cout << name << ": \"mooooooooo\"" << endl;
    }
};

int main() {
    Animal* Animals[10];
    Dog Damo("Damon", 20); Animals[0] = &Damo;
    Dog Gra("Graham", 18); Animals[1] = &Gra;
    Dog Alex("Alex", 22); Animals[2] = &Alex;
    Dog Dave("Dave", 19); Animals[3] = &Dave;
    Cat Lili("Liam", 20); Animals[4] = &Lili;
    Cat Noel("Noel", 20); Animals[5] = &Noel;
    Cow Just("Justine", 18); Animals[6] = &Just;
    Cow Don("Donna", 17); Animals[7] = &Don;
    Cow Ann("Annie", 15); Animals[8] = &Ann;
    Damo.show(); Damo.sound();
    Gra.show(); Gra.sound();
    Alex.show(); Alex.sound();
    Dave.show(); Dave.sound();
    Lili.show(); Lili.sound();
    Noel.show(); Noel.sound();
    Just.show(); Just.sound();
    Don.show(); Don.sound();
    Ann.show(); Ann.sound();
    for (int i = 0; i < Animal::get_count(); i++) {
        Animals[i]->show(); Animals[i]->sound();
    }
    cout << "The animals weigh " << Animal::get_total() << " kg in total."<< endl;
}
*/

class Student {
protected:
    char name[10];
    double politics;
    double english;
    double average;
    double score_s;
public:
    Student(const char* n) {
        strcpy(name, n);
        politics = 0;
        english = 0;
        average = 0;
        score_s = 0;
    }
    void put_politics(double s) {
        politics = s;
    }
    void put_english(double s) {
        english = s;
    }
    virtual void score() {
        average = (politics + english) / 2.0;
        score_s =  average / 20.0;
    }
    void display() {
        score();
        cout << "Student " << name << "\'s average is " << average << "." << endl;
        cout << "Student " << name << "\'s score is " << score_s << "." << endl;
    }
};

class ComputerStudent :public Student {
protected:
    double programming;
public:
    ComputerStudent(const char* n) :Student(n) {
        programming = 0;
    }
    void put_programming(double s) {
        programming = s;
    }
    void score() {
        average = (politics + english + programming) / 3.0;
        score_s = programming / 20.0;
    }
};

class AIStudent :public ComputerStudent {
    double machine_learning;
public:
    AIStudent(const char* n) :ComputerStudent(n) {
        machine_learning = 0;
    }
    void put_machine(double s) {
        machine_learning = s;
    }
    void score() {
        average = (politics + english + programming + machine_learning) / 4.0;
        score_s = machine_learning / 20.0;
    }
};

void display(Student* stu) {
    stu->display();
}

int main() {
    Student* Students[4];

    Student John("John");
    Students[0] = &John;
    John.put_english(88);
    John.put_politics(93);

    ComputerStudent Paul("Paul");
    Students[1] = &Paul;
    Paul.put_english(85);
    Paul.put_politics(90);
    Paul.put_programming(96);

    ComputerStudent George("George");
    Students[2] = &George;
    George.put_english(91);
    George.put_politics(88);
    George.put_programming(87);

    AIStudent Ringo("Ringo");
    Students[3] = &Ringo;
    Ringo.put_english(90);
    Ringo.put_politics(91);
    Ringo.put_programming(95);
    Ringo.put_machine(86);

    for (int i = 0; i < 4; i++)
        display(Students[i]);
    return 0;
}