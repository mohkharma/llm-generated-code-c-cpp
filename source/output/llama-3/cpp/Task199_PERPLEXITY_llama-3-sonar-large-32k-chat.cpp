#include <iostream>

class Clock {
public:
    int hours;
    int minutes;

    Clock(int hours, int minutes) : hours(hours), minutes(minutes) {}

    void addMinutes(int minutes) {
        this->minutes += minutes;
        this->hours += this->minutes / 60;
        this->hours %= 24;
        this->minutes %= 60;
    }

    void subtractMinutes(int minutes) {
        this->minutes -= minutes;
        if (this->minutes < 0) {
            this->hours -= 1;
            this->minutes += 60;
        }
        this->hours %= 24;
        this->minutes %= 60;
    }

    bool operator==(const Clock& other) const {
        return hours == other.hours && minutes == other.minutes;
    }
};

