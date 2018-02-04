//
//  Sphere.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 2/3/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include <stdio.h>
#include "Geometry.hpp"

class Sphere : public Geometry {
private:
    static Sphere * Instance;
public:
    Sphere(int rows = 64, int columns = 64);
    static Sphere * getInstance();
};
#endif /* Sphere_hpp */
