//
//  Dimensions.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/18/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef Dimensions_hpp
#define Dimensions_hpp

#include <stdio.h>

class Dimensions{
public:
    float width;
    float height;
    Dimensions(int width, int height) {
        this->width = 1.0 * width;
        this->height = 1.0 * height;
    }
};

#endif /* Dimensions_hpp */
