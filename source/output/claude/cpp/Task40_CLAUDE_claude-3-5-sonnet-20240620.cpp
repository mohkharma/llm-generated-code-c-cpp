#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <unordered_map>

// Function to generate a random CSRF token
std::string generate_csrf_token() {
    const std::string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string token;
    srand(time(0));
    for (int i = 0; i < 32; ++i) {
        token += charset[rand() % charset.length()];
    }
    return token;
}

// Function to parse query string
std::unordered_map<std::string, std::string> parse_query_string(const std::string& query) {
    std::unordered_map<std::string, std::string> result;
    std::istringstream iss(query);
    std::string pair;
    
    while (std::getline(iss, pair, '&')) {
        size_t pos = pair.find('=');
        if (pos != std::string::npos) {
            std::string key = pair.substr(0, pos);
            std::string value = pair.substr(pos + 1);
            result[key] = value;
        }
    }
    
    return result;
}

// Function to read the stored CSRF token
std::string read_csrf_token() {
    std::ifstream file("/tmp/csrf_token.txt");
    std::string token;
    if (file.is_open()) {
        std::getline(file, token);
        file.close();
    }
    return token;
}

// Function to save the CSRF token
void save_csrf_token(const std::string& token) {
    std::ofstream file("/tmp/csrf_token.txt");
    if (file.is_open()) {
        file << token;
        file.close();
    }
}

int main() {
    std::cout << "Content-type: text/html\r\n\r\n";
    
    std::string request_method = getenv("REQUEST_METHOD") ? getenv("REQUEST_METHOD") : "";
    std::string query_string = getenv("QUERY_STRING") ? getenv("QUERY_STRING") : "";
    
    if (request_method == "POST") {
        // Handle form submission
        std::string post_data;
        std::cin >> post_data;
        auto form_data = parse_query_string(post_data);
        
        std::string stored_token = read_csrf_token();
        std::string submitted_token = form_data["csrf_token"];
        
        if (stored_token == submitted_token && !stored_token.empty()) {
            // CSRF token is valid, process the form
            std::cout << "<h1>Settings Updated</h1>";
            std::cout << "<p>New username: " << form_data["username"] << "</p>";
            std::cout << "<p>New email: " << form_data["email"] << "</p>";
        } else {
            std::cout << "<h1>Error: Invalid CSRF Token</h1>";
        }
        
        std::cout << "<a href='?'>Back to form</a>";
    } else {
        // Display the form
        std::string csrf_token = generate_csrf_token();
        save_csrf_token(csrf_token);
        
        std::cout << "<h1>Update User Settings</h1>";
        std::cout << "<form method='POST'>";
        std::cout << "Username: <input type='text' name='username'><br>";
        std::cout << "Email: <input type='email' name='email'><br>";
        std::cout << "<input type='hidden' name='csrf_token' value='" << csrf_token << "'>";
        std::cout << "<input type='submit' value='Update'>";
        std::cout << "</form>";
    }
    
    return 0;
}