//
//  Light.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/15/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#include <stdio.h>
#include <glm/vec3.hpp>
#include "GLObject.hpp"
class Scene;

class Light: public GLObject {
private:
    friend class Scene;
    void render(Scene* scene) {
        
    }
    glm::vec3 color;
    GLfloat intensity;
public:
    glm::vec3 getPosition();
    Light(GLfloat intensity = 60, glm::vec3 color = glm::vec3(1.0, 1.0, 1.0));
    GLfloat getInensity();
    glm::vec3 getColor();
protected:
};

#endif /* Light_hpp */
