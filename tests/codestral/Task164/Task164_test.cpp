// Task164_Test.cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

// Function exactly as provided
std::vector<std::string> lastNameLenSort(std::vector<std::string> names) {
    auto lastName = [](const std::string& name) {
        std::istringstream iss(name);
        std::string word;
        std::string last;
        while (iss >> word) {
            last = word;
        }
        return last;
    };

    std::sort(names.begin(), names.end(), [&lastName](const std::string& a, const std::string& b) {
        if (lastName(a).length() != lastName(b).length()) {
            return lastName(a).length() < lastName(b).length();
        } else {
            return lastName(a) < lastName(b);
        }
    });

    return names;
}

// Helper: join vector<string> for error messages
std::string join(const std::vector<std::string>& v) {
    std::string res = "[";
    bool first = true;
    for (const auto& s : v) {
        if (!first) res += ", ";
        res += "\"" + s + "\"";
        first = false;
    }
    res += "]";
    return res;
}

bool runTest(const std::vector<std::string>& input, const std::vector<std::string>& expected) {
    auto result = lastNameLenSort(input);
    if (result != expected) {
        std::cerr << "Test failed.\nInput: " << join(input)
                  << "\nExpected: " << join(expected)
                  << "\nGot: " << join(result) << "\n";
        return false;
    }
    return true;
}

int main() {
    struct TestCase {
        std::vector<std::string> input;
        std::vector<std::string> expected;
    };

    TestCase tests[] = {
        {
            {"Jennifer Figueroa","Heather Mcgee","Amanda Schwartz","Nicole Yoder","Melissa Hoffman"},
            {"Heather Mcgee","Nicole Yoder","Melissa Hoffman","Jennifer Figueroa","Amanda Schwartz"}
        },
        {
            {"John Doe","Alice Lee","Bob Zee","Carol Foe"},
            {"Bob Zee","Alice Lee","Carol Foe","John Doe"}
        },
        {
            {"James Bond"},
            {"James Bond"}
        },
        {
            {"Tom Jones","Jerry Jones","Rick Jones","Bob Smith","Paul Smith"},
            {"Bob Smith","Paul Smith","Tom Jones","Jerry Jones","Rick Jones"}
        },
        {
            {"A B","C D","E F","G H","I J"},
            {"A B","C D","E F","G H","I J"}
        },
        {
            {"A B","C Def","E Fghij","G Hijklmn","I J"},
            {"A B","I J","C Def","E Fghij","G Hijklmn"}
        },
        {
            {"Anna Longnamehere","Bob Shortname","Carl Mediumname","Dave Longestnamehere"},
            {"Bob Shortname","Carl Mediumname","Anna Longnamehere","Dave Longestnamehere"}
        },
        {
            {"Alice Wonderland","Bob Marley","Charlie Brown","David Bowie","Edward Norton"},
            {"Bob Marley","David Bowie","Charlie Brown","Edward Norton","Alice Wonderland"}
        },
        {
            {"James Brown","Elijah Davis","Noah Johnson","Liam O'Neill","Oliver Smith"},
            {"James Brown","Elijah Davis","Noah Johnson","Liam O'Neill","Oliver Smith"}
        },
        {
            {"Aaron Smith","Brad Jones","Chris Lee","Derek Adams","Evan Brown"},
            {"Chris Lee","Brad Jones","Aaron Smith","Derek Adams","Evan Brown"}
        }
    };

    bool allPassed = true;
    for (const auto& test : tests) {
        if (!runTest(test.input, test.expected)) {
            allPassed = false;
        }
    }

    if (allPassed) {
        std::cout << "All tests passed successfully.\n";
        return 0;
    } else {
        std::cerr << "Some tests failed.\n";
        return 1;
    }
}
