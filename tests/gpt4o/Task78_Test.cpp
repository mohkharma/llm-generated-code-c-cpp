#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>


bool test_rsa_key_output() {
    // نشغل البرنامج (الذي يولد المفتاح ويطبعه)
    FILE* pipe = popen("./rsa_keygen", "r");  // تأكد أن اسم الملف التنفيذي هو rsa_keygen
    if (!pipe) {
        std::cerr << "Failed to run rsa_keygen" << std::endl;
        return false;
    }

    char buffer[4096];
    std::string output;

    while (fgets(buffer, sizeof(buffer), pipe)) {
        output += buffer;
    }
    int ret = pclose(pipe);

    // تحقق أن المخرجات تبدأ بالمفتاح الخاص RSA PEM
    return output.find("-----BEGIN RSA PRIVATE KEY-----") == 0;
}

int main() {
    if (test_rsa_key_output()) {
        std::cout << "test_generate_rsa_key: PASS" << std::endl;
    } else {
        std::cout << "test_generate_rsa_key: FAIL" << std::endl;
    }
    return 0;
}
