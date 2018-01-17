//
//  Spin.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/7/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef Spin_hpp
#define Spin_hpp

#include <stdio.h>
#include "Script.hpp"
#include "GLObject.hpp"
#include "Light.hpp"


class Spin: public Script<Light> {
public:
    Spin(Light * target);
    virtual void tick();
};

#endif /* Spin_hpp */
