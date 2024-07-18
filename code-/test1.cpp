#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
int64_t convert_to_base10(const std::string& value, int base) {
    int64_t result = 0;
    for (char c : value) {
        result = result * base + (isdigit(c) ? c - '0' : c - 'a' + 10);
    }
    return result;
}
double solve_quadratic(double a, double b, double x, double y) {
    return y - a * x * x - b * x;
}

int main() {
    int n = 4;
    int k = 3;
    std::vector<std::pair<double, double>> points = {
        {1, convert_to_base10("4", 10)},
        {2, convert_to_base10("111", 2)},
        {3, convert_to_base10("12", 10)},
        {6, convert_to_base10("213", 4)}
    };
    if (points.size() < 3) {
        std::cout << "Not enough points to determine the equation." << std::endl;
        return 1;
    }

    std::vector<double> c_values;
    for (size_t i = 0; i < points.size() - 2; ++i) {
        for (size_t j = i + 1; j < points.size() - 1; ++j) {
            for (size_t k = j + 1; k < points.size(); ++k) {
                double x1 = points[i].first, y1 = points[i].second;
                double x2 = points[j].first, y2 = points[j].second;
                double x3 = points[k].first, y3 = points[k].second;
                double a = ((y2 - y1) / (x2 - x1) - (y3 - y1) / (x3 - x1)) / (x2 - x3);
                double b = (y2 - y1) / (x2 - x1) - a * (x1 + x2);
                c_values.push_back(solve_quadratic(a, b, x1, y1));
                c_values.push_back(solve_quadratic(a, b, x2, y2));
                c_values.push_back(solve_quadratic(a, b, x3, y3));
            }
        }
    }
    std::sort(c_values.begin(), c_values.end());
    double c = c_values[c_values.size() / 2];
    int64_t result = std::round(c);
    std::cout << "Estimated c value: " << result << std::endl;

    return 0;
}


