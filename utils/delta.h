#include <iostream>
#include <vector>
#include <cmath>

template <typename T>
std::vector<T> delta(T a, T b, T c) {
    T d = b * b - 4 * a * c;
    if (d < 0) return {};
    auto dsqrt = sqrt(d);

    if (d == 0) {
        return {-b / (2 * a)};
    }
    else {
        return {(-b - dsqrt) / (2 * a), (-b + dsqrt) / (2 * a)};
    }
}

