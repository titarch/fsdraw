//
// Created by bparsy on 1/13/21.
//

#include <utils/vectormath.hh>
#include "Path.hh"

using namespace std::complex_literals;

Path::Path(unsigned int size) : size_(size) {
    points_.reserve(size_);
}

Path Path::from_plain(const std::string& filename) {
    auto file = std::ifstream(filename);
    unsigned size;
    file >> size;

    double x, y;
    std::vector<sf::Vector2<double>> points;
    points.reserve(size);
    for (auto i = 0u; i < size; ++i) {
        file >> x >> y;
        points.emplace_back(x, y);
    }
    vm::normalize2D(points);
    Path path(size);
    for (auto const& point : points) {
        path.points_.emplace_back(point.x, point.y);
//        printf("%lf %lf \n", point.x, point.y);
    }
    return path;
}

auto Path::fs_coef(int n) const -> std::complex<double> {

    const auto dt = 1.0 / double(size_);
    std::complex<double> sum{};
    auto t = 0.0;
    for (auto k = 0u; k < size_; ++k) {
        sum += points_[k] * std::exp(-double(n) * 2.0 * M_PI * 1.0i * t) * (dt * 500);
        t += dt;
    }
    return sum;
}

auto Path::chain(unsigned int size) const -> Chain {
    Chain chain{};
    for (auto i = 1u; i <= size; ++i) {
        const int k = int(i) / 2 * (i % 2 == 0 ? 1 : -1);
        const auto c = fs_coef(k);
        chain.emplace_arrow(std::abs(c), std::arg(c));
    }
    return chain;
}