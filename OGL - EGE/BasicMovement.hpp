//
//  BasicMovement.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/8/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef BasicMovement_hpp
#define BasicMovement_hpp

#include <stdio.h>
#include "Script.hpp"
#include "Camera.hpp"
class BasicMovement : public Script<Camera> {
public:
    virtual void tick(Camera * target);
};

#endif /* BasicMovement_hpp */
