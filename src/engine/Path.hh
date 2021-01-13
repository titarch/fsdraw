//
// Created by bparsy on 1/13/21.
//

#ifndef FSDRAW_PATH_HH
#define FSDRAW_PATH_HH


#include <fstream>
#include <vector>
#include <complex>
#include "Chain.hh"

class Path {
public:
    explicit Path(unsigned size);
    static Path from_plain(std::string const& filename);

    [[nodiscard]] auto fs_coef(int n) const -> std::complex<double>;
    [[nodiscard]] auto chain(unsigned size) const -> Chain;
private:
    unsigned size_;
    std::vector<std::complex<double>> points_{};
};


#endif //FSDRAW_PATH_HH
