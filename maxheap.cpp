#include <iostream>
using namespace std;

void heapify(int a[], int n, int i)
{
    int l = i, left = 2 * i + 1, right = 2 * i + 2;

    if (left < n && a[left] > a[l])
        l = left;
    if (right < n && a[right] > a[l])
        l = right;

    if (l != i)
    {
        swap(a[i], a[l]);
        heapify(a, n, l);
    }
}

int main()
{
    int a[] = {45, 21, 78, 14, 60, 32, 55};
    int n = 7;

    cout << "Given Array:\n";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    cout << "\n\nMax Heap:\n";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
}