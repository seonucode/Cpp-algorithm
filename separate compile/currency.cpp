#include <string>
#include "currency.h"

std::string Asia::Korea::getCurrency() {
    return std::string("KRW");
}

std::string Asia::Singapore::getCurrency() {
    return std::string("SGD");
}

double Asia::Singapore::getInDollar(double krw) {
    return krw / 900;
}

std::string NorthAmerica::USA::getCurrency() {
    return std::string("USD");
}

double NorthAmerica::USA::getInDollar(double krw) {
    return krw / 1200;
}