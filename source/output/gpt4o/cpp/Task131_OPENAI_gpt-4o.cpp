#include <iostream>
#include <fstream>
#include <vector>

class UserData {
public:
    std::string data;
    friend std::ifstream& operator>>(std::ifstream& ifs, UserData& obj) {
        ifs >> obj.data;
        return ifs;
    }
    friend std::ostream& operator<<(std::ostream& os, const UserData& obj) {
        os << obj.data;
        return os;
    }
};
