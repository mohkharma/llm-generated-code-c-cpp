// #include <random>
// #include <cmath>
//
// class Solution {
// private:
//     double radius;
//     double x_center;
//     double y_center;
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_real_distribution<double> dis(0.0, 1.0);
//
// public:
//     Solution(double radius, double x_center, double y_center) : radius(radius), x_center(x_center), y_center(y_center) {}
//
//     std::vector<double> randPoint() {
//         double r = sqrt(dis(gen)) * radius;
//         double theta = dis(gen) * 2 * M_PI;
//         return {x_center + r * cos(theta), y_center + r * sin(theta)};
//     }
// };

#include <random>
#include <cmath>
#include <vector> // Include vector header for std::vector

class Solution {
private:
    double radius;
    double x_center;
    double y_center;
    std::random_device rd; // Random device for seeding
    std::mt19937 gen;      // Mersenne Twister random number generator
    std::uniform_real_distribution<double> dis; // Uniform distribution

public:
    // Constructor
    Solution(double radius, double x_center, double y_center)
        : radius(radius), x_center(x_center), y_center(y_center),
          gen(rd()), dis(0.0, 1.0) {} // Initialize gen and dis here

    std::vector<double> randPoint() {
        double r = sqrt(dis(gen)) * radius; // Generate random radius
        double theta = dis(gen) * 2 * M_PI; // Generate random angle
        return {x_center + r * cos(theta), y_center + r * sin(theta)};
    }
};
