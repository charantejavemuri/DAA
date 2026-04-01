#include <iostream>
using namespace std;

void heapify(int a[], int n, int i)
{
    int s = i, l = 2 * i + 1, r = 2 * i + 2;

    if (l < n && a[l] < a[s])
        s = l;
    if (r < n && a[r] < a[s])
        s = r;

    if (s != i)
    {
        swap(a[i], a[s]);
        heapify(a, n, s);
    }
}

int main()
{
    int a[] = {52, 18, 67, 12, 40, 33, 75};
    int n = 7;

    cout << "Given Array:\n";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    cout << "\n\nMin Heap:\n";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
}