#include <iostream>
using namespace std;

template<class E>
struct Triple {
    int row, col;
    E value;
    Triple* next;
    Triple(int r, int c, E v, Triple* n = NULL) {
        row = r;  col = c;  value = v;
        next = n;
    }
    void operator = (Triple<E>& R) {
        row = R.row;  col = R.col;  value = R.value;
        next = R.next;
    }
};

template <class E>
class SparseMatrix {
public:
    SparseMatrix(int Rw, int Cl);
    int Rows, Cols, Terms;
    Triple<E>* smArray;
};

template <class E>
SparseMatrix<E>::SparseMatrix(int Rw, int Cl) {
    Rows = Rw;   Cols = Cl;   Terms = 0;
    smArray = NULL;
};

template <class E>
E** Multiply(SparseMatrix<E>& a, SparseMatrix<E>& b) {
    E** res = new E * [a.Rows];
    for (int i = 0; i < a.Rows; i++) {
        res[i] = new E[b.Cols];
        for (int j = 0; j < b.Cols; j++)
            res[i][j] = 0;
    }
    for (Triple<E> *An = a.smArray; An != NULL; An = An->next) {
        for (Triple<E> *Bn = b.smArray; Bn != NULL; Bn = Bn->next) {
            if (An->col == Bn->row)
                res[An->row][Bn->col] += An->value * Bn->value;
        }
    }
    return res;
}

int main()
{
    int n, t, m;
    cin >> n >> t >> m;
    SparseMatrix<int> A(n, t);
    SparseMatrix<int> B(t, m);
    int temp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < t; j++) {
            cin >> temp;
            if (temp != 0) {
                Triple<int>* t = new Triple<int>(i, j, temp);
                t->next = A.smArray;
                A.smArray = t;
                A.Terms += 1;
            }
        }
    }
    for (int i = 0; i < t; i++) {
        for (int j = 0; j < m; j++) {
            cin >> temp;
            if (temp != 0) {
                Triple<int>* t = new Triple<int>(i, j, temp);
                t->next = B.smArray;
                B.smArray = t;
                B.Terms += 1;
            }
        }
    }
    int** res = Multiply(A, B);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++)
            cout << res[i][j] << ' ';
        cout << res[i][m - 1] << endl;
    }
    return 0;
}