#include <cmath>
#include <cassert>
#ifndef DERIVATIVES_H
#define DERIVATIVES_H
#endif

#pragma once

typedef long double ld;

namespace ders {

ld secondByYEqu(ld x, ld y) {
    return -1/x + 2*y*std::log(x);
}
ld firstEqu(ld x, ld y) {
    assert(x != 0.);
    return -y/x + y*y*std::log(x);
}
ld secondEqu(ld x, ld y) {
    assert(x != 0.);
    ld fDer = firstEqu(x, y);
    return y/(x*x) + y*y/x + fDer * secondByYEqu(x, y);
}
ld thirdEqu(ld x, ld y) {
    assert(x != 0.);
    ld fDer = firstEqu(x, y);
    ld sDer = secondEqu(x, y);
    return -2.*y/(x*x*x) - y*y/(x*x) + 2*(1./(x*x) + 2*y/x)*fDer
            + 2*std::log(x)*fDer*fDer + secondByYEqu(x, y)*sDer;
}
ld firstYSys(ld x, ld y, ld z) {
    return std::exp(-y*y-z*z) + 2*x;
}
ld firstZSys(ld x, ld y, ld z) {
    return 2*y*y + z + 0*x;
}

ld solution(ld x) {
    return -2./(x + x*log(x)*log(x));
}
}
