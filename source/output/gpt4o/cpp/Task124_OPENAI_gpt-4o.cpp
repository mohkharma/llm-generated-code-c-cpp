// C++ code
#include <iostream>
#include <unordered_map>
#include <string>

class SensitiveData {
    private:
        std::unordered_map<std::string, std::string> data;

    public:
        void storeData(const std::string& key, const std::string& value) {
            data[key] = value;
        }

        std::string retrieveData(const std::string& key) {
            auto it = data.find(key);
            if (it != data.end()) {
                return it->second;
            }
            return "Data not found";
        }
};
