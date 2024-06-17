#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Word {
private:
    string self;
    string tag;
    int count;
    bool has_conjunction;
    friend bool Conjuction(Word& a, Word& b);
public:
    Word() {
        self = "";
        tag = "";
        count = 0;
        has_conjunction = false;
    }
    void operator=(const Word& w) {
        self = w.self;
        tag = w.tag;
        count = w.count;
        has_conjunction = w.has_conjunction;
    }
    bool operator<(const Word& w) {
        return (tag < w.tag) || (tag == w.tag && self < w.self);
    }
    bool operator==(const Word& w) {
        return (self == w.self);
    }
    bool operator>(const Word& w) {
        return (tag > w.tag) || (tag == w.tag && self > w.self);
    }
    bool operator<=(const Word& w) {
        return (tag < w.tag) || (tag == w.tag && self <= w.self);
    }
    bool operator>=(const Word& w) {
        return (tag > w.tag) || (tag == w.tag && self >= w.self);
    }
    void Update(string s) {
        self = s;
        tag = s;
        sort(tag.begin(), tag.end());
        count = 1;
    }
    void AddCount(Word& w) {
        count = w.count + 1;
    }
    int GetCount() {
        return count;
    }
    void UpdateSame(Word& w) {
        count = w.count + 1;
        has_conjunction = w.has_conjunction;
    }
    void Print() {
        cout << endl;
        cout << self;
        cout << " " << tag << " " << count << " " << has_conjunction;
    }
    void FoundConjunction() {
        has_conjunction = true;
    }
    bool HasConjunction() {
        return has_conjunction;
    }
    string GetSelf() {
        return self;
    }
};

bool Conjuction(Word& a, Word& b) {
    //return (a.tag == b.tag) && (a.self != b.self);
    return a.tag == b.tag;
}

template <class T>
void Swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
int Partition(T*& list, int p, int r) {
    T pivot = list[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (list[j] < pivot) {
            i = i + 1;
            Swap<T>(list[i], list[j]);
        }
    }
    Swap<T>(list[i + 1], list[r]);
    return i + 1;
}

template <class T>
void QuickSort(T*& list, int p, int r) {
    if (p < r) {
        int q = Partition<T>(list, p, r);
        QuickSort(list, p, q - 1);
        QuickSort(list, q + 1, r);
    }
}

int main()
{
    int n;
    cin >> n;
    Word* words = new Word[n];
    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        words[i].Update(s);
    }
    QuickSort<Word>(words, 0, n - 1);
    int word_count = 0;
    /*for (int i = 0; i < n; i++) {
        words[i].Print();
    }*/
    for (int i = n - 1; i > 0; i--) {
        //if (words[i] == words[i - 1])
            //words[i - 1].UpdateSame(words[i]);
        if (Conjuction(words[i], words[i - 1])) {
            words[i - 1].AddCount(words[i]);
            if (!words[i].HasConjunction())
                word_count++;
            words[i - 1].FoundConjunction();
            //words[i - 1].Print();
            //words[i].Print();
        }
    }
    /*for (int i = 0; i < n; i++) {
        words[i].Print();
    }*/
    cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
    cout << word_count;
    int index = 0;
    int result_index = 0;
    int temp_count;
    string* result = new string[word_count];
    while (index < n) {
        temp_count = words[index].GetCount();
        if (words[index].HasConjunction()) {
            result[result_index] = words[index].GetSelf();
            result_index++;
        }
        index += temp_count;
    }
    QuickSort<string>(result, 0, word_count - 1);
    for (int i = 0; i < word_count; i++)
        cout << '\n' << result[i];
    return 0;
}