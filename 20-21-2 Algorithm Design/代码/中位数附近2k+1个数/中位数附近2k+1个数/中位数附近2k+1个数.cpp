#include <iostream>
using namespace std;

int Partition(int*& list, int p, int r) {
    int pivot = list[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (list[j] < pivot) {
            i = i + 1;
            swap(list[i], list[j]);
        }
    }
    swap(list[i + 1], list[r]);
    return i + 1;
}

int PartitionBy(int*& list, int p, int r, int num) {
    for (int j = p; j < r; j++) {
        if (list[j] == num) {
            swap(list[j], list[r]);
            break;
        }
    }
    return Partition(list, p, r);
}

void QuickSort(int*& list, int p, int r) {
    if (p < r) {
        int q = Partition(list, p, r);
        QuickSort(list, p, q - 1);
        QuickSort(list, q + 1, r);
    }
}

void InsertSort(int*& list, int p, int r) {
    for (int j = p; j <= r; j++) {
        int temp = list[j];
        int i = j - 1;
        while (i > p && list[i] > temp) {
            list[i + 1] = list[i];
            i--;
        }
        list[i + 1] = temp;
    }
}

int SelectELinear(int*& list, int p, int r, int k) {
    if (p >= r) return p;
    int q = Partition(list, p, r);
    if (k == q)
        return q;
    else if (k < q)
        return SelectELinear(list, p, q - 1, k);
    else
        return SelectELinear(list, q + 1, r, k);
}

int SelectWLinear(int*& list, int p, int r, int k) {
    if (p >= r) return k;
    int count_median = (r - p + 4) / 5;
    int* medians = new int[count_median];
    int max_index = count_median - 1;
    int max_group = max_index * 5;
    int index = 0;
    for (index = 0; index < max_index; index++) {
        InsertSort(list, index * 5, index * 5 + 4);
        medians[index] = list[index * 5 + 2];
    }
    InsertSort(list, max_group, r);
    medians[count_median - 1] = list[(max_group + r) / 2];
    int median_index = SelectWLinear(medians, 0, max_index, max_index / 2);
    int median = medians[median_index];
    int x = PartitionBy(list, p, r, median);
    delete[]medians;
    if (k == x)
        return x;
    else if (k < x)
        return SelectWLinear(list, p, x - 1, k);
    else
        return SelectWLinear(list, x + 1, r, k);
}

int main()
{
    int k, n;
    cin >> k >> n;
    int* list = new int[n];
    for (int i = 0; i < n; i++)
        cin >> list[i];
    int index_median = (n - 1) / 2;
    int index_first = SelectELinear(list, 0, n - 1, index_median - k);
    int index_last = SelectELinear(list, index_median - k + 1, n - 1, index_median + k);
    int total = 2 * k + 1;
    int* result = new int[total];
    for (int i = 0; i < total; i++)
        result[i] = list[index_first + i];
    QuickSort(result, 0, total - 1);
    for (int i = 0; i < total - 1; i++)
        cout << result[i] << ' ';
    cout << result[total - 1];
    return 0;
}