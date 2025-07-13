// C++
#include <iostream>

class Session {
    private:
        int userId;
        bool isActive;

    public:
        Session(int userId) {
            this->userId = userId;
            this->isActive = true;
        }

        void endSession() {
            this->isActive = false;
        }
    int getUserId() const {
            return userId;
        }

    bool getIsActive() const {
            return isActive;
        }

};

