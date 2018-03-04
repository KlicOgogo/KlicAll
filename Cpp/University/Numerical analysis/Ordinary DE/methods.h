#include <algorithm>
#include "series.h"
#include <vector>
#include <iomanip>
#include <cmath>
#ifndef METHODS_H
#define METHODS_H
#endif

#pragma once

typedef long double ld;

std::pair<ld, ld>  solveSI(ld x, ld y, ld z, ld yOne, ld zOne, ld step) {
    ld zOld = zOne;
    ld yOld = yOne;
    ld yNew = yOld + (step/12)*((-1)*ders::firstYSys(x-step, y, z) +
              8*ders::firstYSys(x, yOne, zOne) + 5*ders::firstYSys(x+step, yOld, zOld));
    ld zNew = zOld + (step/12)*((-1)*ders::firstZSys(x-step, y, z) +
              8*ders::firstZSys(x, yOne, zOne) + 5*ders::firstZSys(x+step, yOld, zOld));
    while (std::abs(zNew - zOld) > 1e-5 || std::abs(yNew - yOld) > 1e-5) {
        zOld = zNew;
        yOld = yNew;
        yNew = yOne + (step/12)*((-1)*ders::firstYSys(x-step, y, z) +
                  8*ders::firstYSys(x, yOne, zOne) + 5*ders::firstYSys(x+step, yOld, zOld));
        zNew = zOne + (step/12)*((-1)*ders::firstZSys(x-step, y, z) +
                  8*ders::firstZSys(x, yOne, zOne) + 5*ders::firstZSys(x+step, yOld, zOld));
    }
    return std::make_pair(yNew, zNew);
}

ld solveN(ld x, ld y, ld step) {
    ld yOld = y;
    ld yNew = yOld - (yOld-y-step*ders::firstEqu(x, yOld))/(1.-step*ders::secondByYEqu(x, yOld));
    while (std::abs(yOld - yNew) > 1e-5) {
        yOld = yNew;
        yNew = yOld - (yOld-y-step*ders::firstEqu(x, yOld))/(1.-step*ders::secondByYEqu(x, yOld));
    }
    return yNew;
}
std::pair<ld, ld> sovleSI(ld x, ld y, ld z, ld step) {
    ld zOld = z;
    ld yOld = y;
    ld yNew = yOld + step*ders::firstYSys(x, yOld, zOld);
    ld zNew = zOld + step*ders::firstZSys(x, yOld, zOld);
    while (std::abs(zNew - zOld) > 1e-5 || std::abs(yNew - yOld) > 1e-5) {
        yOld = yNew;
        zOld = zNew;
        yNew = y + step*ders::firstYSys(x, yOld, zOld);
        zNew = z + step*ders::firstZSys(x, yOld, zOld);
    }
    return std::make_pair(yNew, zNew);
}

namespace methods {
std::vector<ld> exactSolution(ld x, ld xl, ld step) {
    std::cout << "Exact values of solution\n";
    std::vector<ld> result;
    for (ld i = x; i < xl+0.0001; i += step) {
        if (i != x) {
            std::cout << "u(" << i << ") = " << std::setprecision(10) <<  ders::solution(i);
            result.push_back(ders::solution(i));
            if (static_cast<int>((i-x)/step) % 2 == 0) {
                std:: cout << '\n';
            } else {
                std::cout << ";    ";
            }
        }
    }
    std::cout << '\n';
    return result;
}
std::vector<ld> series(ld x, ld xl, ld y, ld step) {
    std::cout << "Result of series method for one equation:\n";
    Series mainSeries(x, y);
    std::vector<ld> result;
    for (ld i = x; i < xl+0.0001; i+= step) {
        y = mainSeries.countSeriesAtPoint(i);
        if (i != x) {
            std::cout << "y(" << i << ") = " << std::setprecision(10) <<  y;
            result.push_back(y);
            if (static_cast<int>((i-x)/step) % 2 == 0) {
                std:: cout << '\n';
            } else {
                std::cout << ";    ";
            }
        }
        Series newSeries(i, y);
        mainSeries = newSeries;
    }
    std::cout << '\n';
    return result;
}
std::vector<ld> EulerExp(ld x, ld xl, ld y, ld step) {
    std::cout << "Result of Eulerian explicit method for one equation\n";
    std::vector<ld> result;
    for (ld i = x; i < xl+0.0001; i += step) {
        if (i != x) {
            std::cout << "y(" << i << ") = " << std::setprecision(10) <<  y;
            result.push_back(y);
            if (static_cast<int>((i-x)/step) % 2 == 0) {
                std:: cout << '\n';
            } else {
                std::cout << ";    ";
            }
        }
        y += step*ders::firstEqu(i, y);
    }
    std::cout << '\n';
    return result;
}
std::vector<std::pair<ld,ld> > EulerExp(ld x, ld xl, ld y, ld z, ld step) {
    std::vector<std::pair<ld,ld> > result;
    std::cout << "Result of Eulerian explicit method for system\n";
    for (ld i = x; i < xl+0.0001; i += step) {
       if (i != x) {
           std::cout << "y(" << i << ") = " << std::setprecision(10) <<  y << ";    ";
           std::cout << "z(" << i << ") = " << std::setprecision(10) <<  z << '\n';
           result.push_back(std::make_pair(y,z));
       }
       y += step*ders::firstYSys(i, y, z);
       z += step*ders::firstZSys(i, y, z);
    }
    std::cout << '\n';
    return result;
}
std::vector<ld> EulerImp(ld x, ld xl, ld y, ld step) {
    std::cout << "Result of Eulerian implicit method for one equation:\n";
    std::vector<ld> result;
    for (ld i = x; i < xl+0.0001; i += step) {
        if (i != x) {
            std::cout << "y(" << i << ") = " << std::setprecision(10) <<  y;
            result.push_back(y);
            if (static_cast<int>((i-x)/step) % 2 == 0) {
                std:: cout << '\n';
            } else {
                std::cout << ";    ";
            }
        }
        y = solveN(i+step, y, step);
    }
    std::cout << '\n';
    return result;
}
std::vector<std::pair<ld,ld> > EulerImp(ld x, ld xl, ld y, ld z, ld step) {
    std::cout << "Result of Eulerian implicit method for system\n";
    std::vector<std::pair<ld,ld> > result;
    for (ld i = x; i < xl+0.0001; i += step) {
       if ( i != x) {
           std::cout << "y(" << i << ") = " << std::setprecision(10) <<  y << ";    ";
           std::cout << "z(" << i << ") = " << std::setprecision(10) <<  z << '\n';
           result.push_back(std::make_pair(y,z));
       }
       y = sovleSI(i+step, y, z, step).first;
       z = sovleSI(i+step, y, z, step).second;
    }
    std::cout << '\n';
    return result;
}
std::vector<ld> PredictorCorrector(ld x, ld xl, ld y, ld step) {
    std::cout << "Result of predictor-corrector method for one equation:\n";
    ld xHalf, yHalf, yNext;
    std::vector<ld> result;
    for (ld i = x; i < xl+0.0001; i += step) {
        if (i != x) {
            std::cout << "y(" << i << ") = " << std::setprecision(10) <<  y;
            result.push_back(y);
            if (static_cast<int>((i-x)/step) % 2 == 0) {
                std:: cout << '\n';
            } else {
                std::cout << ";    ";
            }
        }
        xHalf = i+step/2;
        yHalf = y + (step/2)*ders::firstEqu(i, y);
        yHalf = y + (step/4)*(ders::firstEqu(i, y) + ders::firstEqu(xHalf, yHalf));
        yNext = y + step*ders::firstEqu(i, y);
        yNext = y + (step/2)*(ders::firstEqu(i, y) + ders::firstEqu(i+step, yNext));
        y = y + (step/6)*(ders::firstEqu(i, y) + 4*ders::firstEqu(xHalf, yHalf) + ders::firstEqu(i+step, yNext));
    }
    std::cout << '\n';
    return result;
}
std::vector<std::pair<ld,ld> > PredictorCorrector(ld x, ld xl, ld y, ld z, ld step) {
    std::cout << "Result of predictor-corrector method for system:\n";
    std::vector<std::pair<ld,ld> > result;
    ld zNew, yNew, zTemp, yTemp;
    for (ld i = x; i < xl+0.0001; i += step) {
       if (i != x) {
           std::cout << "y(" << i << ") = " << std::setprecision(10) <<  y << ";    ";
           std::cout << "z(" << i << ") = " << std::setprecision(10) <<  z << '\n';
           result.push_back(std::make_pair(y,z));
       }
       zNew = z + step*ders::firstZSys(i, y, z);
       yNew = y + step*ders::firstYSys(i, y ,z);
       zTemp = z + (step/2)*(ders::firstZSys(i, y ,z) + ders::firstZSys(i+step, yNew, zNew));
       yTemp = y + (step/2)*(ders::firstYSys(i, y, z) + ders::firstYSys(i+step, yNew, zNew));
       z = zTemp;
       y = yTemp;
    }
    std::cout << '\n';
    return result;
}
std::vector<ld> RungeKutta(ld x, ld xl, ld y, ld step) {
    std::cout << "Result of Runge-Kutta method for one equation:\n";
    std::vector<ld> result;
    ld fiZer, fiOne;
    for (ld i = x; i < xl+0.0001; i += step) {
        if (i != x) {
            std::cout << "y(" << i << ") = " << std::setprecision(10) <<  y;
            result.push_back(y);
            if (static_cast<int>((i-x)/step) % 2 == 0) {
                std:: cout << '\n';
            } else {
                std::cout << ";    ";
            }
        }
       fiZer = step*ders::firstEqu(i, y);
       fiOne = step*ders::firstEqu(i+step/2, y+fiZer/2);
       y += fiOne;
    }
    std::cout << '\n';
    return result;
}
std::vector<std::pair<ld,ld> > RungeKutta(ld x, ld xl, ld y, ld z, ld step) {
    std::cout << "Result of Runge-Kutta method for system:\n";
    std::vector<std::pair<ld,ld> > result;
    ld fiZZer, fiZOne, fiZTwo, fiYZer, fiYOne, fiYTwo;
    for (ld i = x; i < xl+0.0001; i += step) {
       if (i != x) {
           std::cout << "y(" << i << ") = " << std::setprecision(10) <<  y << ";    ";
           std::cout << "z(" << i << ") = " << std::setprecision(10) <<  z << '\n';
           result.push_back(std::make_pair(y,z));
       }
       fiYZer = step*ders::firstYSys(i, y, z);
       fiZZer = step*ders::firstZSys(i, y, z);
       fiYOne = step*ders::firstYSys(i+step/3, y+fiYZer/3, z+fiZZer/3);
       fiZOne = step*ders::firstZSys(i+step/3, y+fiYZer/3, z+fiZZer/3);
       fiYTwo = step*ders::firstYSys(i+2*step/3, y+2*fiYOne/3, z+2*fiZOne/3);
       fiZTwo = step*ders::firstZSys(i+2*step/3, y+2*fiYOne/3, z+2*fiZOne/3);
       y += fiYZer/4 + 0*fiYOne + 3*fiYTwo/4;
       z += fiZZer/4 + 0*fiZOne + 3*fiZTwo/4;
    }
    std::cout << '\n';
    return result;
}
std::vector<ld> ExtAdams(ld x, ld xl, ld y, ld step) {
    std::cout << "Result of Extrapolate Adams' method for one equation\n";
    std::vector<ld> result;
    ld xHalf, yHalf, yOne, yTwo;
    xHalf = x+step/2;
    yHalf = y + (step/2)*ders::firstEqu(x, y);
    yHalf = y + (step/4)*(ders::firstEqu(x, y) + ders::firstEqu(xHalf, yHalf));
    yOne = y + step*ders::firstEqu(x, y);
    yOne = y + (step/2)*(ders::firstEqu(x, y) + ders::firstEqu(x+step, yOne));
    yOne = y + (step/6)*(ders::firstEqu(x, y) + 4*ders::firstEqu(xHalf, yHalf) + ders::firstEqu(x+step, yOne));
    xHalf += step;
    yHalf = yOne + (step/2)*ders::firstEqu(x+step, yOne);
    yHalf = yOne + (step/4)*(ders::firstEqu(x+step, yOne) + ders::firstEqu(xHalf, yHalf));
    yTwo = yOne + step*ders::firstEqu(x+step, yOne);
    yTwo = yOne + (step/2)*(ders::firstEqu(x+step, yOne) + ders::firstEqu(x+step*2, yTwo));
    yTwo = yOne + (step/6)*(ders::firstEqu(x+step, yOne) + 4*ders::firstEqu(xHalf, yHalf) + ders::firstEqu(x+step*2, yTwo));
    ld yTemp;
    std::cout << "y(" << x+step << ") = " << std::setprecision(10) <<  yOne << ";    ";
    result.push_back(yOne);
    for (ld i = x+2*step; i < xl+0.0001; i += step) {
        if (i != x) {
            std::cout << "y(" << i << ") = " << std::setprecision(10) <<  yTwo;
            result.push_back(yTwo);
            if (static_cast<int>((i-x)/step) % 2 == 0) {
                std:: cout << '\n';
            } else {
                std::cout << ";    ";
            }
        }
        yTemp = yTwo + (step/12)*(23*ders::firstEqu(i, yTwo) - 16*ders::firstEqu(i-step, yOne) + 5*ders::firstEqu(i-step*2, y));
        std::swap(yTemp, yTwo);
        std::swap(yTemp, yOne);
        std::swap(yTemp, y);
    }
    std::cout << '\n';
    return result;
}
std::vector<std::pair<ld,ld> > IntAdams(ld x, ld xl, ld y, ld z, ld step) {
    std::cout << "Result of Interpolate Adams' method for system\n";
    std::vector<std::pair<ld,ld> > result;
    ld zOne, yOne, zTemp, yTemp;
    zOne = z + step*ders::firstZSys(x, y, z);
    yOne = y + step*ders::firstYSys(x, y ,z);
    zTemp = z + (step/2)*(ders::firstZSys(x, y, z) + ders::firstZSys(x+step, yOne, zOne));
    yTemp = y + (step/2)*(ders::firstYSys(x, y ,z) + ders::firstYSys(x+step, yOne, zOne));
    zOne = zTemp;
    yOne = yTemp;
    for (ld i = x+step; i < xl+0.0001; i += step) {
       if (i != x) {
           std::cout << "y(" << i << ") = " << std::setprecision(10) <<  yOne << ";    ";
           std::cout << "z(" << i << ") = " << std::setprecision(10) <<  zOne << '\n';
           result.push_back(std::make_pair(yOne, zOne));
       }
       yTemp = solveSI(i, y, z, yOne, zOne, step).first;
       zTemp = solveSI(i, yOne, z, yTemp, zOne, step).second;
       std::swap(yTemp, yOne);
       std::swap(zTemp, zOne);
       std::swap(yTemp, y);
       std::swap(zTemp, z);
    }
    std::cout << '\n';
    return result;
}
}
