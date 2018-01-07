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


class Spin: public Script<GLObject> {
public:
    virtual void tick(GLObject * target);
};

#endif /* Spin_hpp */
