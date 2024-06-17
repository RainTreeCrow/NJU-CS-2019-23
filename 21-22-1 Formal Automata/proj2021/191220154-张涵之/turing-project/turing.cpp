#include "turing.h"

void printSyntaxError(int current_line, string error_msg) {
    cerr << "syntax error at line " << current_line << ", " << error_msg << endl;
    exit(-1);
}

void printSyntaxErrorWOLine(string error_msg) {
    cerr << "syntax error, " << error_msg << endl;
    exit(-1);
}

vector<char> splitChar(string str, char spliter, int line) {
    vector<char> result;
    istringstream iss(str);
    string token;
    while (getline(iss, token, spliter)) {
        if (token.size() != 1)
            printSyntaxError(line, "expect symbol to be one single character");
        else
            result.push_back(token[0]);
    }
    return result;
}

vector<string> splitString(string str, char spliter) {
    vector<string> result;
    istringstream iss(str);
    string token;
    while (getline(iss, token, spliter)) {
        if (token.size() > 0)
            result.push_back(token);
    }
    return result;
}

TuringMachine::TuringMachine(ifstream &tm, bool v) {
    verbose_mode_on = v;
    string current_line;
    int current_line_cnt = 0;
    while (getline(tm, current_line)) {
        current_line_cnt++;
        // blanck line
        // cout << current_line << endl;
        if (current_line.size() == 0)
            continue;
        // annotation
        else if (current_line[0] == ';')
            continue;
        else {
            vector<string> tokens = splitString(current_line, ' ');
            /*for (int i = 0; i < tokens.size(); i++) {
                cout << "\"" << tokens[i] << "\" ";
            }
            cout << endl;*/
            string first = tokens[0];
            if (first[0] == '#') {
                if (tokens.size() < 3)
                    printSyntaxError(current_line_cnt, "definition incomplete");
                // more annotation
                else if (tokens.size() > 3 && tokens[3][0] != ';')
                    printSyntaxError(current_line_cnt, "unknown type");
                else if (tokens[1] != "=")
                    printSyntaxError(current_line_cnt, "missing \"=\" in definition");
                else {
                    string third = tokens[2];
                    int token_length = third.length();
                    // states
                    if (first == "#Q") {
                        // check if Q is a set (with a pair of "{}")
                        if (third[0] != '{' || third[token_length - 1] != '}') 
                            printSyntaxError(current_line_cnt, "need a set for Q");
                        else
                            states = splitString(third.substr(1, token_length - 2), ',');
                    }
                    // input alphabet
                    else if (first == "#S") {
                        // check if S is a set
                        if (third[0] != '{' || third[token_length - 1] != '}')
                            printSyntaxError(current_line_cnt, "need a set for S");
                        else
                            input_alphabet = splitChar(third.substr(1, token_length - 2), ',', current_line_cnt);
                    }
                    // tape alphabet
                    else if (first == "#G") {
                        // check if G is a set
                        if (third[0] != '{' || third[token_length - 1] != '}')
                            printSyntaxError(current_line_cnt,"need a set for G");
                        else
                            tape_alphabet = splitChar(third.substr(1, token_length - 2), ',', current_line_cnt);
                    }
                    // start state
                    else if (first == "#q0")
                        start_state = third;
                    // blank symbol
                    else if (first == "#B")
                        blank_symbol = third[0];
                    // final states
                    else if (first == "#F") {
                        // check if F is a set
                        if (third[0] != '{' || third[token_length - 1] != '}')
                            printSyntaxError(current_line_cnt, "need a set for F");
                        else
                            final_states = splitString(third.substr(1, token_length - 2), ',');
                    }
                    // number of states
                    else if (first == "#N") {
                        // check if N is an integer
                        for (int i = 0; i < token_length; i++) {
                            if (third[i] < '0' || third[i] > '9')
                                printSyntaxError(current_line_cnt, "need an integer for N");
                        }
                        number_of_tapes = stoi(third);
                    }
                    else {
                        printSyntaxError(current_line_cnt, "unknown definition");
                        exit(-1);
                    }
                }
            }
            else { //transition function
                if (tokens.size() < 5)
                    printSyntaxError(current_line_cnt, "transition function incomplete");
                // more annotation
                else if (tokens.size() > 5 && tokens[5][0] != ';')
                    printSyntaxError(current_line_cnt, "unknown type");
                else {
                    string in_s = tokens[0];
                    string in_t = tokens[1];
                    string new_t = tokens[2];
                    string d = tokens[3];
                    string new_s = tokens[4];
                    transition_function.push_back(TransFunc(in_s, in_t, new_t, d, new_s));
                }
            }
        }
    }
    checkSelf();
    //printSelf();
}

void TuringMachine::checkSelf() {
    bool found_start = false;
    bool* found_final = new bool[final_states.size()];
    bool* found_delta_in = new bool[transition_function.size()];
    bool* found_delta_new = new bool[transition_function.size()];
    for (int i = 0; i < final_states.size(); i++)
        found_final[i] = false;
    for (int i = 0; i < transition_function.size(); i++) {
        found_delta_in[i] = false;
        found_delta_new[i] = false;
    }
    for (int i = 0; i < states.size(); i++) {
        string temp = states[i];
        for (int j = 0; j < temp.size(); j++) {
            char ch = temp[j];
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '_')
                continue;
            else
                printSyntaxErrorWOLine("illegal expression in state definition");
        }
        if (temp == start_state)
            found_start = true;
        for (int k = 0; k < final_states.size(); k++) {
            if (temp == final_states[k])
                found_final[k] = true;
        }
        for (int l = 0; l < transition_function.size(); l++) {
            if (temp == transition_function[l].in_state)
                found_delta_in[l] = true;
            if (temp == transition_function[l].new_state)
                found_delta_new[l] = true;
        }
    }
    if (!found_start)
        printSyntaxErrorWOLine("start state does not belong to all defined states");
    for (int i = 0; i < final_states.size(); i++) {
        if (!found_final[i])
            printSyntaxErrorWOLine("final states are not contained in all defined states");
    }
    for (int i = 0; i < transition_function.size(); i++) {
        if (!found_delta_in[i])
            printSyntaxErrorWOLine("transition function has an non-existent input state");
        if (!found_delta_new[i])
            printSyntaxErrorWOLine("transition function has an non-existent output state");
        string in_symbol = transition_function[i].in_tape_symbol;
        string new_symbol = transition_function[i].new_tape_symbol;
        string diretion = transition_function[i].direction;
        if (in_symbol.size() != number_of_tapes)
            printSyntaxErrorWOLine("transition function has input tape symbol of wrong length");
        if (new_symbol.size() != number_of_tapes)
            printSyntaxErrorWOLine("transition function has output tape symbol of wrong length");
        if (diretion.size() != number_of_tapes)
            printSyntaxErrorWOLine("transition function has direction of wrong length");
        for (int j = 0; j < diretion.size(); j++) {
            if (diretion[j] != 'l' && diretion[j] != 'r' && diretion[j] != '*')
                printSyntaxErrorWOLine("expect \'l\' , \'r\' or \'*\' for directions");
        }
    }
    for (int i = 0; i < input_alphabet.size(); i++) {
        char ch = input_alphabet[i];
        if (ch == ' ' || ch == ',' || ch == ';' || ch == '{' || ch == '}' || ch == '*' || ch == '_')
            printSyntaxErrorWOLine("illegal symbol for input alphabet");
    }
    for (int i = 0; i < tape_alphabet.size(); i++) {
        char ch = tape_alphabet[i];
        if (ch == ' ' || ch == ',' || ch == ';' || ch == '{' || ch == '}' || ch == '*')
            printSyntaxErrorWOLine("illegal symbol for tape alphabet");
    }
    if (blank_symbol != '_')
        printSyntaxErrorWOLine("blank symbol should have been \"_\"");
}

bool TuringMachine::legalInput(string input) {
    int first_illegal_ch = -1;
    for (int i = 0; i < input.size(); i++) {
        bool flag = false;
        char ch = input[i];
        for (int j = 0; j < input_alphabet.size(); j++) {
            if (ch == input_alphabet[j]) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            first_illegal_ch = i;
            break;
        }
    }
    if (first_illegal_ch == -1)
        return true;
    if (!verbose_mode_on) {
        cerr << "illegal input" << endl;
        exit(-1);
    }
    else {
        cerr << "Input: " << input << endl;
        cerr << "==================== ERR ====================" << endl;
        cerr << "error: \'" << input[first_illegal_ch];
        cerr << "\' was not declared in the set of input symbols" << endl;
        cerr << "Input: " << input << endl;
        cerr << "       ";
        for (int i = 0; i < first_illegal_ch; i++)
            cerr << " ";
        cerr << "^" << endl;
        cerr << "==================== END ====================" << endl;
        exit(-1);
    }
}

void TuringMachine::printStep() {
    cout << "Step\t: " << step << endl;
    for (int i = 0; i < number_of_tapes; i++) {
        int leftmost = tapes[i].leftmost;
        cout << "Index" << i << "\t: ";
        for (int j = 0; j < tapes[i].content.size() - 1; j++) {
            cout << abs(j + leftmost) << " ";
        }
        int pos = tapes[i].content.size() - 1 + leftmost;
        cout << abs(pos) << endl;
        cout << "Tape" << i << "\t: ";

        for (int j = 0; j < tapes[i].content.size() - 1; j++) {
            cout << tapes[i].content[j];
            int temp = abs(j + leftmost);
            ostringstream os;
            os << temp;
            int cnt = (os.str()).size();
            //cout << endl << temp << " " << cnt << endl;
            for (int k = 0; k < cnt; k++)
                cout << " ";
        }
        cout << tapes[i].content[tapes[i].content.size() - 1] << endl;
        cout << "Head" << i << "\t: ";
        for (int j = tapes[i].leftmost; j < tapes[i].index; j++) {
            cout << " ";
            int temp = abs(j);
            ostringstream os;
            os << temp;
            int cnt = (os.str()).size();
            for (int k = 0; k < cnt; k++)
                cout << " ";
        }
        cout << "^" << endl;
    }
    cout << "State\t: " << current_state << endl;
    cout << "---------------------------------------------" << endl;
}

void TuringMachine::Simulate(string input) {
    if (!legalInput(input))
        return;
    step = 0;
    for (int i = 0; i < number_of_tapes; i++) {
        Tape temp;
        tapes.push_back(temp);
    }
    if (input.size() == 0)
        input = "_";
    tapes[0].content = input;
    current_state = start_state;
    if (verbose_mode_on) {
        cout << "Input: " << input << endl;
        cout << "==================== RUN ====================" << endl;
        printStep();
    }
    while (true) {
        for (int k = 0; k < final_states.size(); k++) {
            if (current_state == final_states[k])
                break;
        }
        step++;
        int find_trans_func = -1;
        bool* flag = new bool[transition_function.size()];
        int* paired_cnt = new int[transition_function.size()];
        for (int i = 0; i < transition_function.size(); i++) {
            flag[i] = true;
            paired_cnt[i] = 0;
        }
        for (int i = 0; i < transition_function.size(); i++) {
            if (transition_function[i].in_state != current_state) {
                flag[i] = false;
                continue;
            }
            for (int j = 0; j < number_of_tapes; j++) {
                if (transition_function[i].in_tape_symbol[j] == tapes[j].content[tapes[j].index - tapes[j].leftmost])
                    paired_cnt[i]++;
                else if (transition_function[i].in_tape_symbol[j] == '*')
                    continue;
                else
                    flag[i] = false;
            }
        }
        int max_paired = -1;
        for (int i = 0; i < transition_function.size(); i++) {
            if (flag[i] && paired_cnt[i] > max_paired) {
                find_trans_func = i;
                max_paired = paired_cnt[i];
            }
        }
        if (find_trans_func == -1)
            break;
        for (int j = 0; j < number_of_tapes; j++) {
            char ch = transition_function[find_trans_func].new_tape_symbol[j];
            if (ch != '*')
            tapes[j].content[tapes[j].index - tapes[j].leftmost] = ch;
            if (transition_function[find_trans_func].direction[j] == 'r') {
                tapes[j].index++;
                if (tapes[j].index - tapes[j].leftmost >= tapes[j].content.size())
                    tapes[j].content.push_back(blank_symbol);
            }
            else if (transition_function[find_trans_func].direction[j] == 'l') {
                tapes[j].index--;
                if (tapes[j].index < tapes[j].leftmost) {
                    tapes[j].content.insert(0, 1, blank_symbol);
                    tapes[j].leftmost--;
                }
            }
        }
        current_state = transition_function[find_trans_func].new_state;
        eraseBlankfromTapes();
        if (verbose_mode_on)
            printStep();
    }
    string result = tapes[0].content;
    if (verbose_mode_on) {
        cout << "Result: " << result << endl;
        cout << "==================== END ====================" << endl;
    }
    else
        cout << result << endl;
}

void TuringMachine::eraseBlankfromTapes() {
    for (int i = 0; i < number_of_tapes; i++) {
        for (int j = 0; j < tapes[i].index - tapes[i].leftmost; ) {
            if (tapes[i].content[j] == blank_symbol && tapes[i].content.size() > 1) {
                tapes[i].content.erase(0, 1);
                tapes[i].leftmost++;
            }
            else
                break;
        }
        for (int k = tapes[i].content.size() - 1; k > tapes[i].index - tapes[i].leftmost; ) {
            if (tapes[i].content[k] == blank_symbol && tapes[i].content.size() > 1) {
                tapes[i].content.pop_back();
                k--;
            }
            else
                break;
        }
    }
}

void TuringMachine::printSelf() {
    cout << "#Q = {";
    for (int i = 0; i < states.size() - 1; i++)
        cout << states[i] << ",";
    cout << states[states.size() - 1] << "}" << endl;
    cout << "#S = {";
    for (int i = 0; i < input_alphabet.size() - 1; i++)
        cout << input_alphabet[i] << ',';
    cout << input_alphabet[input_alphabet.size() - 1] << "}" << endl;
    cout << "#G = {";
    for (int i = 0; i < tape_alphabet.size() - 1; i++)
        cout << tape_alphabet[i] << ',';
    cout << tape_alphabet[tape_alphabet.size() - 1] << "}" << endl;
    cout << "#q0 = " << start_state << endl;
    cout << "#B = " << blank_symbol << endl;
    cout << "#F = {";
    for (int i = 0; i <final_states.size() - 1; i++)
        cout << final_states[i] << ',';
    cout << final_states[final_states.size() - 1] << "}" << endl;
    cout << "#N = " << number_of_tapes << endl;
    for (int i = 0; i < transition_function.size(); i++) {
        cout << transition_function[i].in_state << " " << transition_function[i].in_tape_symbol;
        cout << " " << transition_function[i].new_tape_symbol << " ";
        cout << transition_function[i].direction << " " << transition_function[i].new_state << endl;
    }
}