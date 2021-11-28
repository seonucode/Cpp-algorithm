#include <string>

namespace Asia {
    namespace Korea {
        std::string getCurrency();
    }
    namespace Singapore {
        std::string getCurrency();
        double getInDollar(double krw);
    }
}

namespace NorthAmerica {
    namespace USA {
        std::string getCurrency();
        double getInDollar(double krw);
    }
}