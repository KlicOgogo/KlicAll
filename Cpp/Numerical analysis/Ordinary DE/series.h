#include "derivatives.h"
#include <vector>
#ifndef SERIES_H
#define SERIES_H

#endif
#pragma once

typedef long double ld;
class Series {
public:
    Series() = default;
    Series(ld x, ld y) {
        koeff_.resize(4);
        koeff_[0] = y;
        koeff_[1] = ders::firstEqu(x, y);
        koeff_[2] = ders::secondEqu(x, y)/2.;
        koeff_[3] = ders::thirdEqu(x, y)/6.;
        x_ = x;
    }
    Series(const Series& Series): koeff_(Series.koeff_), x_(Series.x_) {}
    Series& operator=(Series& Series) {
        koeff_.clear();
        koeff_.resize(Series.koeff_.size());
        for (size_t i = 0; i < koeff_.size(); i++) {
            koeff_[i] = Series.koeff_[i];
        }
        x_ = Series.x_;
        return *this;
    }
    Series(const std::vector<ld>& koeff, const ld& x): koeff_(koeff), x_(x) {}
    void print() {
        std::cout << "y(x)=";
        for (size_t j = 0; j < koeff_.size(); j++) {
            if (koeff_[j] >= 0) {
                std::cout << koeff_[j];
            } else if (koeff_[j] < 0) {
                std::cout << "(" << koeff_[j] << ")";
            }
            if (j == 0) {
                std::cout << "";
            } else {
                if (x_ < 0) {
                    std::cout << "(x+" << (-1) * x_ << ")^" << j << "";
                } else if (x_ > 0) {
                    std::cout << "(x-" << x_ << ")^" << j << "";
                } else {
                      std::cout << "(x)^" << j << "";
                }
            }
            if (j != koeff_.size() - 1) {
                std::cout << "+";
            }
        }
        std::cout << std::endl;
    }
    ld countSeriesAtPoint(ld point) {
        ld result = 0;
        for (size_t i = 0; i < koeff_.size(); i++) {
            result += koeff_[i]*pow(point-x_, static_cast<ld>(i));
        }
        return result;
    }
private:
    std::vector<ld> koeff_;
    ld x_;
};
