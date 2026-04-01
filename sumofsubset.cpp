#include <iostream>
using namespace std;

int subset[100], n, target;
int arr[100];

void findSubset(int i, int sum) {
    if (sum == target) {
        cout << "{ ";
        for (int j = 0; j < i; j++) {
            cout << subset[j] << " ";
        }
        cout << "}" << endl;
        return;
    }

    if (i >= n || sum > target)
        return;

    // Include current element
    subset[i] = arr[i];
    findSubset(i + 1, sum + arr[i]);

    // Exclude current element
    findSubset(i + 1, sum);
}

int main() {
    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cout << "Enter target sum: ";
    cin >> target;

    cout << "Subsets with given sum:\n";
    findSubset(0, 0);

    return 0;
}