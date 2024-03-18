#include <iostream>
#include <vector>
#include <cmath>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

cpp_int find_inverse(cpp_int number, cpp_int modulus) {
    return powm(number, modulus - 2, modulus);
}

class Point {
private:
    cpp_int x;
    cpp_int y;
    std::vector<cpp_int> j_config;

public:
    Point(cpp_int x_val, cpp_int y_val, std::vector<cpp_int> config) {
        x = x_val;
        y = y_val;
        j_config = config;
    }

    bool is_equal_to(Point point) {
        return x == point.x && y == point.y;
    }

    Point add(Point point) {
        cpp_int p = j_config[2];
        cpp_int slope;

        if (is_equal_to(point)) {
            slope = (3 * pow(point.x, 2)) * find_inverse(2 * point.y, p) % p;
        } else {
            slope = (point.y - y) * find_inverse(point.x - x, p) % p;
        }

        cpp_int new_x = (pow(slope, 2) - point.x - x) % p;
        cpp_int new_y = (slope * (x - new_x) - y) % p;
        return Point(new_x, new_y, j_config);
    }

    Point multiply(cpp_int times) {
        Point current_point = *this;
        cpp_int current_coefficient = 1;

        std::vector<std::pair<cpp_int, Point>> previous_points;
        while (current_coefficient < times) {
            previous_points.push_back(std::make_pair(current_coefficient, current_point));
            if (2 * current_coefficient <= times) {
                current_point = current_point.add(current_point);
                current_coefficient = 2 * current_coefficient;
            } else {
                Point next_point = *this;
                cpp_int next_coefficient = 1;
                for (auto &prev_point : previous_points) {
                    if (prev_point.first + current_coefficient <= times) {
                        if (prev_point.second.x != current_point.x) {
                            next_coefficient = prev_point.first;
                            next_point = prev_point.second;
                        }
                    }
                }
                current_point = current_point.add(next_point);
                current_coefficient = current_coefficient + next_coefficient;
            }
        }

        return current_point;
    }

    cpp_int get_x() {
        return x;
    }

    cpp_int get_y() {
        return y;
    }
};

int main() {
    std::vector<cpp_int> d_j_config = {0, 7, 115792089237316195423570985008687907853269984665640564039457584007908834671663};
    cpp_int x = 103388573995635080359749164254216598308788835304023601477803095234286494993683;
    cpp_int y = 37057141145242123013015316630864329550140216928701153669873286428255828810018;
    Point dj_point(x, y, d_j_config);

    cpp_int target_r = cpp_int("0x4f084dbe6e33d6efcbb62e4f094855c89629f83e15ff98a8c2a35edd5e95f959");

    cpp_int k = 5555555555555555555;
    int counter = 0;

    while (true) {
        ++counter;
        Point r_point = dj_point.multiply(k);
        cpp_int r = r_point.get_x();
        std::cout << counter << ") " << r << std::endl;
        ++k;
        if (r == target_r) {
            std::cout << "Найдено значение r, соответствующее целевому значению." << std::endl;
            break;
        }
    }

    return 0;
}
