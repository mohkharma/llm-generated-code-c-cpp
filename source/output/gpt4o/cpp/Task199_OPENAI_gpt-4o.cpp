#include <iostream>
#include <iomanip>

class Clock {
private:
    int hour;
    int minute;

    void normalize() {
        if (minute >= 60) {
            hour += minute / 60;
            minute %= 60;
        }
        while (minute < 0) {
            hour -= 1;
            minute += 60;
        }
        hour = (hour + 24) % 24;
    }

public:
    Clock(int h, int m) : hour(h), minute(m) { normalize(); }

    void addMinutes(int minutes) {
        minute += minutes;
        normalize();
    }

    void subtractMinutes(int minutes) {
        minute -= minutes;
        normalize();
    }

    bool operator==(const Clock& other) const {
        return hour == other.hour && minute == other.minute;
    }

    friend std::ostream& operator<<(std::ostream& os, const Clock& clock) {
        os << std::setw(2) << std::setfill('0') << clock.hour << ":"
        << std::setw(2) << std::setfill('0') << clock.minute;
        return os;
    }
};

