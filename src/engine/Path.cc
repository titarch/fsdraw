//
// Created by bparsy on 1/13/21.
//

#include <utils/vectormath.hh>
#include "Path.hh"

using namespace std::complex_literals;

Path::Path(float radius) : radius_(radius) {}

Path Path::from_plain(const std::string& filename, float radius) {
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
    auto path = Path(radius);
    path.points_.reserve(size);
    for (auto const& point : points)
        path.points_.emplace_back(point.x, point.y);
    return path;
}

void Path::linear_interpolation(unsigned int new_pts_per_pts) {
    auto newpts = decltype(points_){};
    newpts.reserve(points_.size() * new_pts_per_pts);
    const auto step = 1.0 / double(new_pts_per_pts + 1);
    for (auto i = 0u; i < points_.size() - 1; ++i) {
        newpts.push_back(points_[i]);
        for (auto k = 1u; k <= new_pts_per_pts; ++k) {
            const auto t = double(k) * step;
            const auto real = std::lerp(points_[i].real(), points_[i + 1].real(), t);
            const auto imag = std::lerp(points_[i].imag(), points_[i + 1].imag(), t);
            newpts.emplace_back(real, imag);
        }
    }
    newpts.push_back(points_.back());
    points_ = newpts;
}

auto Path::fs_coef(int n) const -> std::complex<double> {
    const auto dt = 1.0 / double(points_.size());
    std::complex<double> sum{};
    auto t = 0.0;
    for (auto k = 0u; k < points_.size(); ++k) {
        sum += points_[k] * std::exp(-double(n) * 2.0 * M_PI * 1.0i * t) * (dt * radius_);
        t += dt;
    }
    return sum;
}

auto Path::chain(unsigned int size) const -> Chain {
    Chain chain{};
    for (auto i = 1u; i <= size; ++i) {
        const int k = int(i) / 2 * (i % 2 == 0 ? 1 : -1);
        chain.emplace_arrow(fs_coef(k));
    }
    return chain;
}