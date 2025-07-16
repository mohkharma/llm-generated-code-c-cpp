#include <iostream>
#include <string>
#include <sqlite3.h>

struct CustomerInfo {
    int id;
    std::string username;
    std::string name;
    std::string email;
    std::string phone;
};

CustomerInfo* getCustomerInfo(const std::string& username) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    CustomerInfo* customer = nullptr;

    // افتح القاعدة مع المسار الكامل
    if (sqlite3_open("/home/kali/CLionProjects/llm-generated-code-cpp/tests/claude/Task67/customer_database.db", &db) == SQLITE_OK) {
        std::string sql = "SELECT * FROM customer WHERE username = ?";
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                customer = new CustomerInfo;
                customer->id = sqlite3_column_int(stmt, 0);
                customer->username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                customer->name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
                customer->email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
                customer->phone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            }

            sqlite3_finalize(stmt);
        }
        sqlite3_close(db);
    }

    return customer;
}

// دالة مساعدة للمقارنة وطباعة النتائج
bool compareCustomer(const CustomerInfo* c1, const CustomerInfo* c2) {
    if (!c1 || !c2) return false;
    return c1->id == c2->id &&
           c1->username == c2->username &&
           c1->name == c2->name &&
           c1->email == c2->email &&
           c1->phone == c2->phone;
}

void printCustomer(const CustomerInfo* c) {
    if (!c) {
        std::cout << "Customer not found.\n";
        return;
    }
    std::cout << "id: " << c->id << "\n";
    std::cout << "username: " << c->username << "\n";
    std::cout << "name: " << c->name << "\n";
    std::cout << "email: " << c->email << "\n";
    std::cout << "phone: " << c->phone << "\n";
}

void run_tests() {
    // هنا نضيف اختبارين، واحد موجود، وواحد غير موجود (مطابق للبايثون: موجود أو لا)

    // مثال: غير معروف اسم المستخدم، نتوقع nullptr
    CustomerInfo* c;

    // 1) موجود - غيّر "testuser" إلى اسم مستخدم صحيح في قاعدة البيانات
    std::string existing_username = "testuser";

    c = getCustomerInfo(existing_username);
    if (c != nullptr) {
        std::cout << "Test case 1 (existing username): PASS\n";
        printCustomer(c);
        delete c;
    } else {
        std::cout << "Test case 1 (existing username): FAIL\n";
    }

    // 2) غير موجود
    std::string non_existing_username = "username_that_does_not_exist_123456";

    c = getCustomerInfo(non_existing_username);
    if (c == nullptr) {
        std::cout << "Test case 2 (non-existing username): PASS\n";
    } else {
        std::cout << "Test case 2 (non-existing username): FAIL\n";
        delete c;
    }
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        std::string username = argv[1];
        CustomerInfo* c = getCustomerInfo(username);
        if (c) {
            std::cout << "Customer Information:\n";
            printCustomer(c);
            delete c;
        } else {
            std::cout << "Customer not found.\n";
        }
        return 0;
    }

    run_tests();

    return 0;
}
