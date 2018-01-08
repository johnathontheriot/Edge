//
//  Spin.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/7/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "Spin.hpp"
#include "GLObject.hpp"

void Spin::tick(GLObject * target) {
    target->rotateLocal((179 * M_PI) / 180, (179 * M_PI) / 180, -(179 * M_PI) / 180);
}
