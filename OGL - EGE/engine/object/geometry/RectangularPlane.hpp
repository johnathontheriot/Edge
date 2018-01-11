//
//  RectangularPlane.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/10/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef RectangularPlane_hpp
#define RectangularPlane_hpp

#include <stdio.h>

#include "Geometry.hpp"

class RectangularPlane : public Geometry {
private:
    int rows;
    int columns;
    static RectangularPlane * Instance;
    RectangularPlane();
public:
    RectangularPlane(int, int);
    RectangularPlane(int, int, GLfloat*);
    void generateVertices(GLfloat * uvs);
    static RectangularPlane * getInstance();
};

#endif /* RectangularPlane_hpp */
