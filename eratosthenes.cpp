#include <iostream>
#include <array>
using namespace std;

const int MAX_N = 300;

int main() {
    int n;
    cin >> n;
    array<int, MAX_N> arr = {0, };

    // Initialization of the array
    for (array<int, MAX_N>::iterator iter = arr.begin();
         iter < arr.begin() + n; iter++) 
    {
        *iter = iter - arr.begin() + 1;
    }

    // Changing non-prime numbers to 0, in Eratosthenes method
    for (array<int, MAX_N>::iterator iter1 = arr.begin();
         iter1 < arr.begin() + n; iter1++) 
    {
        if (iter1 == arr.begin()) *iter1 = 0;
        for (array<int, MAX_N>::iterator iter2 = iter1 + 1;
             iter2 < arr.begin() + n; iter2++)
        {
            if (*iter1 != 0 && *iter2 % *iter1 == 0) *iter2 = 0;
        }
    }

    // Print out the result array
    for (array<int, MAX_N>::iterator iter = arr.begin();
         iter < arr.begin() + n; iter++)
    {
        cout << *iter;
        if (iter < arr.begin() + n - 1) cout << " ";
    }

    return 0;
}