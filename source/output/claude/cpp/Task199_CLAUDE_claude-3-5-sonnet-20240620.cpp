
#include <iostream>
#include <iomanip>

class Clock {
private:
    int minutes;

public:
    Clock(int hour, int minute) : minutes((hour * 60 + minute) % 1440) {}

    friend std::ostream& operator<<(std::ostream& os, const Clock& clock) {
        int hours = clock.minutes / 60;
        int mins = clock.minutes % 60;
        os << std::setfill('0') << std::setw(2) << hours << ":" 
           << std::setfill('0') << std::setw(2) << mins;
        return os;
    }

    bool operator==(const Clock& other) const {
        return minutes == other.minutes;
    }

    Clock& add(int mins) {
        minutes = (minutes + mins) % 1440;
        return *this;
    }

    Clock& subtract(int mins) {
        minutes = (minutes - mins + 1440) % 1440;
        return *this;
    }
};
