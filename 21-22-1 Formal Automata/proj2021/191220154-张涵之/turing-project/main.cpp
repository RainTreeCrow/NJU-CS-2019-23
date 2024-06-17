#include "turing.h"

int main(int argc, char** argv)
{
    if (argc <= 1) return 1;
    if (strcmp (argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << endl;
        return 1;
    }
    else if (strcmp (argv[1], "-v") == 0 || strcmp(argv[1], "-verbose") == 0) {
        // TODO: verbose
        if (argc <= 3) {
            cerr << "imput not found" << endl;
            return -1;
        }
        ifstream tm(argv[2]);
        if (!tm) { 
            cerr << "tm file no found" << endl;
            return -1;
        }
        TuringMachine TM(tm, true);
        string input = argv[3];
        TM.Simulate(input);
            return 1;
    }
    else if (argv[1][0] == '-') {
        cout << "unknown command, type -h for help" << endl;
        return -1;
    }
    if (argc <= 2) {
        cerr << "imput not found" << endl;
        return -1;
    }
    ifstream tm(argv[1]);
    if (!tm) { 
        cerr << "tm file no found" << endl;
        return -1;
    }
    TuringMachine TM(tm, false);
    string input = argv[2];
    TM.Simulate(input);
    return 0;
}