#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

/*
class StrOperation {
private:
    string str;
public:
    StrOperation(string s) {
        str = s;
    }
    bool judgePalindrome() {
        bool flag = true;
        for (int i = 0; i < str.length() / 2; i++) {
            if (str[i] != str[str.length() - i - 1]) {
                flag = false;
                break;
            }
        }
        return flag;
    }
    void insertStr(int i, string s) {
        str.insert(i, s);
    }
    void replaceStr(int be, int en, string s) {
        str.replace(be - 1, en - be + 1, s);
    }
    void print() {
        cout << str << endl;
    }
};

int main()
{
    StrOperation Op1("Helloworld");
    StrOperation Op2("afgcgfa");
    StrOperation Op3("an egg gge na");
    cout << Op1.judgePalindrome() << endl;
    cout << Op2.judgePalindrome() << endl;
    cout << Op3.judgePalindrome() << endl;
    Op1.insertStr(5, " ");
    Op1.print();
    Op1.insertStr(11, "!!!");
    Op1.print();
    Op1.replaceStr(7, 11, "Liam");
    Op1.print();
    Op1.replaceStr(1, 5, "Goodbye");
    Op1.print();
    return 0;
}
*/

/*
class Animal {
    string name;
    int num;
    friend class System;
public:
    Animal(string n, int m) {
        name = n;
        num = m;
    }
};

class System {
    vector<Animal> Animals;
    int species;
    int total;
public:
    System() {
        vector<Animal> Animals;
        species = 0;
        total = 0;
    }
    void addAnimal(Animal a) {
        if (Animals.size() == 0) {
            Animals.push_back(a);
            species += 1;
            total += a.num;
        }
        else {
            bool exist = false;
            vector<Animal>::iterator it;
            it = Animals.begin();
            for (; it != Animals.end(); it++) {
                if (a.name.compare(it->name) == 0) {
                    exist = true;
                    it->num += a.num;
                    break;
                }
                else if (a.name.compare(it->name) > 0) {
                    it++;
                    break;
                }
            }
            if (!exist) {
                Animals.insert(it, a);
                species += 1;
                total += a.num;
            }
        }
    }
    void deleteAnimal(string name) {
        bool exist = false;
        vector<Animal>::iterator it;
        it = Animals.begin();
        for (; it != Animals.end(); it++) {
            if (name.compare(it->name) == 0) {
                exist = true;
                break;
            }
        }
        if (exist) {
            species -= 1;
            total -= it->num;
            Animals.erase(it);
        }
        else
            cout << "Animal does not exist!" << endl;
    }
    int searchAnimal(string name) {
        bool exist = false;
        vector<Animal>::iterator it;
        it = Animals.begin();
        for (; it != Animals.end(); it++) {
            if (name.compare(it->name) == 0) {
                exist = true;
                break;
            }
        }
        if (exist)
            return it->num;
        else
            return 0;
    }
    void countAnimals() {
        cout << "There are " << species << " species, " << total << " animals in total." << endl;
    }
    void displayAnimals() {
        vector<Animal>::iterator it;
        it = Animals.begin();
        for (; it != Animals.end(); it++)
            cout << "There are " << it->num << " " << it->name << "(s)." << endl;
    }
};

int main()
{
    System sys;
    Animal cat("cat", 3);
    Animal dog("dog", 5);
    Animal horse("horse", 2);
    Animal fish("fish", 10);
    sys.addAnimal(cat);
    sys.addAnimal(fish);
    sys.addAnimal(horse);
    sys.addAnimal(dog);
    sys.displayAnimals();
    sys.countAnimals();
    sys.deleteAnimal("cat");
    sys.deleteAnimal("horse");
    cout << "Found " << sys.searchAnimal("cat") << " cat(s)."<< endl;
    cout << "Found " << sys.searchAnimal("fish") << " fish(s)." << endl;
    sys.displayAnimals();
    sys.countAnimals();
}
*/

class Book {
    int number;
    string name;
    string author;
    int year;
    friend class MachineVector;
    friend class MachineList;
    friend class MachineMap;
public:
    Book(int num, string n, string a, int y) {
        number = num;
        name = n;
        author = a;
        year = y;
    }
};

class MachineVector {
    vector<Book> Books;
    int number;
public:
    MachineVector() {
        vector<Book> Books;
        number = 1000;
    }
    void addBook2(int num, string name, string author, int year) {
        for (int i = 0; i < num; i++)
            Books.push_back(Book(number + i, name, author, year));
        number += num;
    }
    void deleteBook(int ID) {
        bool exist = false;
        vector<Book>::iterator it;
        it = Books.begin();
        for (; it != Books.end(); it++) {
            if (it->number == ID) {
                exist = true;
                break;
            }
        }
        if (exist) {
            Books.erase(it);
        }
    }
    void searchBook(string name) {
        bool exist = false;
        int count = 0;
        vector<int> id;
        vector<Book>::iterator it;
        it = Books.begin();
        for (; it != Books.end(); it++) {
            if (name.compare(it->name) == 0) {
                exist = true;
                count += 1;
                id.push_back(it->number);
            }
        }
        cout << "Found " << count << " " << name << "(s)." << endl;
        if (exist) {
            cout << "Their ID are: ";
            for_each(id.begin(), id.end(), [](int i) {cout << i << ' '; });
            cout << endl;
        }
    }
    void sortAndDisplay() {
        sort(Books.begin(), Books.end(), [](Book b1, Book b2) { return b1.year < b2.year; });
        for_each(Books.begin(), Books.end(), [](Book b) {
            cout << b.number << '\t' << b.name << '\t' << b.author << '\t' << b.year << endl;
            }
        );
    }
    void searchAuthor(string author) {
        bool exist = false;
        int count = 0;
        vector<int> id;
        vector<Book>::iterator it;
        it = Books.begin();
        for (; it != Books.end(); it++) {
            if (author.compare(it->author) == 0) {
                exist = true;
                count += 1;
                id.push_back(it->number);
            }
        }
        cout << "Found " << count << " book(s) by " << author << "." << endl;
        if (exist) {
            cout << "Their ID are: ";
            for_each(id.begin(), id.end(), [](int i) {cout << i << ' '; });
            cout << endl;
        }
    }
};

class MachineList {
    list<Book> Books;
    int number;
public:
    MachineList() {
        list<Book> Books;
        number = 1000;
    }
    void addBook2(int num, string name, string author, int year) {
        for (int i = 0; i < num; i++)
            Books.push_back(Book(number + i, name, author, year));
        number += num;
    }
    void deleteBook(int ID) {
        bool exist = false;
        list<Book>::iterator it;
        it = Books.begin();
        for (; it != Books.end(); it++) {
            if (it->number == ID) {
                exist = true;
                break;
            }
        }
        if (exist) {
            Books.erase(it);
        }
    }
    void searchBook(string name) {
        bool exist = false;
        int count = 0;
        vector<int> id;
        list<Book>::iterator it;
        it = Books.begin();
        for (; it != Books.end(); it++) {
            if (name.compare(it->name) == 0) {
                exist = true;
                count += 1;
                id.push_back(it->number);
            }
        }
        cout << "Found " << count << " " << name << "(s)." << endl;
        if (exist) {
            cout << "Their ID are: ";
            for_each(id.begin(), id.end(), [](int i) {cout << i << ' '; });
            cout << endl;
        }
    }
    void sortAndDisplay() {
        Books.sort([](Book b1, Book b2) { return b1.year < b2.year; });
        for_each(Books.begin(), Books.end(), [](Book b) {
            cout << b.number << '\t' << b.name << '\t' << b.author << '\t' << b.year << endl;
            }
        );
    }
    void searchAuthor(string author) {
        bool exist = false;
        int count = 0;
        vector<int> id;
        list<Book>::iterator it;
        it = Books.begin();
        for (; it != Books.end(); it++) {
            if (author.compare(it->author) == 0) {
                exist = true;
                count += 1;
                id.push_back(it->number);
            }
        }
        cout << "Found " << count << " book(s) by " << author << "." << endl;
        if (exist) {
            cout << "Their ID are: ";
            for_each(id.begin(), id.end(), [](int i) {cout << i << ' '; });
            cout << endl;
        }
    }
};

int main()
{
    clock_t a1, b1;
    a1 = clock();
    MachineVector mac_v;
    mac_v.addBook2(100, "Japan & Self Existence", "Mick Karn", 2009);
    mac_v.addBook2(50, "Bit of a Blur", "Alex James", 2005);
    mac_v.addBook2(50, "The Seed and the Sower", "Lawrence Van der Post", 1983);
    mac_v.addBook2(100, "A Far Off Place", "Lawrence Van der Post", 1993);
    mac_v.addBook2(200, "Turquoise Days: the Weird World of Echo & the Bunnymen", "Chris Adams", 1997);
    mac_v.deleteBook(1050);
    mac_v.deleteBook(1100);
    mac_v.deleteBook(3000);
    mac_v.searchBook("Bit of a Blur");
    mac_v.searchBook("Turquoise Days: the Weird World of Echo & the Bunnymen");
    mac_v.searchBook("Call Me by Your Name");
    mac_v.sortAndDisplay();
    mac_v.searchAuthor("Mick Karn");
    mac_v.searchAuthor("Lawrence Van der Post");
    mac_v.searchAuthor("Philip K. Dick");
    b1 = clock();
    double d1 = (double)(b1 - a1) / CLOCKS_PER_SEC;

    clock_t a2, b2;
    a2 = clock();
    MachineList mac_l;
    mac_l.addBook2(10, "Japan & Self Existence", "Mick Karn", 2009);
    mac_l.addBook2(5, "Bit of a Blur", "Alex James", 2005);
    mac_l.addBook2(50, "The Seed and the Sower", "Lawrence Van der Post", 1983);
    mac_l.addBook2(100, "A Far Off Place", "Lawrence Van der Post", 1993);
    mac_l.addBook2(20, "The Weird World of Echo & the Bunnymen", "Chris Adams", 1997);
    mac_l.deleteBook(1050);
    mac_l.deleteBook(1100);
    mac_l.deleteBook(3000);
    mac_l.searchBook("Bit of a Blur");
    mac_l.searchBook("The Weird World of Echo & the Bunnymen");
    mac_l.searchBook("Call Me by Your Name");
    mac_l.sortAndDisplay();
    mac_l.searchAuthor("Mick Karn");
    mac_l.searchAuthor("Lawrence Van der Post");
    mac_l.searchAuthor("Philip K. Dick");
    b2 = clock();
    double d2 = (double)(b2 - a2) / CLOCKS_PER_SEC;

    cout << d1 << ' ' << d2 << endl;

    return 0;
}