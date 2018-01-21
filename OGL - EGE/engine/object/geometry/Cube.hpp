//
//  Cube.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/7/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef Cube_hpp
#define Cube_hpp

#include <stdio.h>
#include "Geometry.hpp"

class Cube : public Geometry {
private:
    friend class SkyBox;
    static Cube * Instance;
public:
    Cube();
    static Cube * getInstance();
};


#endif /* Cube_hpp */
