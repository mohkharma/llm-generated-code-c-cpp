// Task164_Test.cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Provided function exactly as given
std::vector<std::string> lastNameLensort(std::vector<std::string> names) {
    std::sort(names.begin(), names.end(), [](const std::string& s1, const std::string& s2) {
        size_t space1 = s1.find(' ');
        size_t space2 = s2.find(' ');
        std::string lastName1 = s1.substr(space1 + 1);
        std::string lastName2 = s2.substr(space2 + 1);
        if (lastName1.length() != lastName2.length()) {
            return lastName1.length() < lastName2.length();
        } else {
            return lastName1 < lastName2;
        }
    });
    return names;
}

// Helper to format vector<string> as string
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

// Test runner
bool runTest(const std::vector<std::string>& input, const std::vector<std::string>& expected) {
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
