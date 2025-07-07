// Task164_Test.cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

// Provided function exactly as given
std::vector<std::string> lastNameLensort(std::vector<std::string> &names) {
    auto getLastName = [](const std::string &name) -> std::string {
        std::istringstream ss(name);
        std::string firstName, lastName;
        ss >> firstName >> lastName;
        return lastName;
    };

    std::sort(names.begin(), names.end(), [&](const std::string &a, const std::string &b) {
        std::string lastNameA = getLastName(a);
        std::string lastNameB = getLastName(b);
        if (lastNameA.length() == lastNameB.length()) {
            return lastNameA < lastNameB;
        }
        return lastNameA.length() < lastNameB.length();
    });

    return names;
}

// Helper to join vector<string> for debug output
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

// Test runner function
bool runTest(std::vector<std::string> input, const std::vector<std::string>& expected) {
    auto result = lastNameLensort(input);
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
