//
//  Camera.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/6/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include <glm/mat4x4.hpp>

class Camera {
private:
public:
    glm::mat4x4 viewMatrix;
    Camera();
};

#endif /* Camera_hpp */
