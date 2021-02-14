//
// Created by 유승우 on 2020/04/22.
//

#ifndef FIRSTRAYTRACER_RAY_HPP
#define FIRSTRAYTRACER_RAY_HPP

#include <cmath>
#include <cstdlib>
#include <iostream>
#include "vector3.hpp"

class ray{
public:
    ray() {
        // Do nothing
    }

    ray(const point3& origin, const vector3& direction, double time = 0.0)
            : orig(origin), dir(direction), tm(time) {
        // Do nothing
    }

    point3 origin() const {
        return orig;
    }

    vector3 direction() const {
        return dir;
    }

    double time() const {
        return tm;
    }

    vector3 at(double t) const {
        return orig + t * dir;
    }

public:
    point3 orig;
    vector3 dir;
    double tm;
};

#endif //FIRSTRAYTRACER_RAY_HPP
