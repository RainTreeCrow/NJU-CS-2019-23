#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <string>
#include <vector>
using namespace std;

void printSyntaxError(int current_line, string error_msg);
void printSyntaxErrorWOLine(string error_msg);
vector<char> splitChar(string str, char spliter, int line);
vector<string> splitString(string str, char spliter);

struct TransFunc {
    string      in_state;
    string      in_tape_symbol;
    string      new_tape_symbol;
    string      direction;
    string      new_state;
    TransFunc(string inS, string inT, string nT, string d, string nS) {
        in_state = inS;
        in_tape_symbol = inT;
        new_state = nS;
        new_tape_symbol = nT;
        direction = d;
    }
};

struct Tape {
    string  content;
    int     index;
    int     leftmost;
    Tape() {
        content = "_";
        index = 0;
        leftmost = 0;
    }
};

class TuringMachine {
protected:
    // static parameters
    vector<string>      states;
    vector<char>        input_alphabet;
    vector<char>        tape_alphabet;
    string              start_state;
    vector<TransFunc>   transition_function;
    char                blank_symbol;
    vector<string>      final_states;
    int                 number_of_tapes;
    bool                verbose_mode_on;
    // dynamic parameters
    int                 step;
    vector<Tape>        tapes;
    string              current_state;
public:
    TuringMachine() {}
    TuringMachine(ifstream &tm, bool v);
    void checkSelf();
    bool legalInput(string input);
    void printStep();
    void Simulate(string input);
    void eraseBlankfromTapes();
    void printSelf();
};