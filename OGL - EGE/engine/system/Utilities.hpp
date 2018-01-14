//
//  Utilities.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/13/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef Utilities_hpp
#define Utilities_hpp

#include <stdio.h>
#include <glm/vec4.hpp>

class Utilities {
private:
public:
    static glm::vec4 toColor(int hex) {
        int sig = 0x000000FF;
        int r = (hex >> 24) & sig;
        int g = (hex >> 16) & sig;
        int b = (hex >> 8) & sig;
        int a = hex & sig;
        return glm::vec4((r * 1.0f) / 255.0f, (g * 1.0f) / 255.0f, (b * 1.0f) / 255.0f, (a * 1.0f) / 255.0f);
    }
protected:
};

#endif /* Utilities_hpp */
