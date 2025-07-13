#include <iostream>
#include <string>

class SensitiveData {
private:
    std::string data;

public:
    SensitiveData(std::string data) {
        this->data = data;
    }

    std::string getData() {
        return data;
    }
};
