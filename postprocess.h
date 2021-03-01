//
// Created by tudor on 17/02/2021.
//

#ifndef POSTPROCESS_H
#define POSTPROCESS_H

#include <cmath>

#include "vec3.h"


class postprocess {
public:
    static void gamma(vec3 &col, float gamma) {
        col.set_x(static_cast<float>(pow(col.x(), 1.0 / gamma)));
        col.set_y(static_cast<float>(pow(col.y(), 1.0 / gamma)));
        col.set_z(static_cast<float>(pow(col.z(), 1.0 / gamma)));
    }
};

#endif //POSTPROCESS_H
