#include <iostream>
#include "currency.h"
using namespace std;

int main() {
    double krw;
    cout << "Enter the amount of money you want to exchange: ";
    cin >> krw;
    cout << "The amount of money: " << krw << " " << Asia::Korea::getCurrency() << endl;
    {
        using namespace Asia::Singapore;
        cout << "In Singapore dollar: " << getInDollar(krw) << " " << getCurrency() << endl;
    }
    {
        using namespace NorthAmerica::USA;
        cout << "In USA dollar: " << getInDollar(krw) << " " << getCurrency() << endl;
    }
    return 0;
}