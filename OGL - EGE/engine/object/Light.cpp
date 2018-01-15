//
//  Light.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/15/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "Light.hpp"

glm::vec3 Light::getPosition() {
    return this->getModelMatrix() * glm::vec4(0.0, 0.0, 0.0, 1.0);
}

Light::Light(GLfloat intensity, glm::vec3 color): GLObject() {
    this->intensity = intensity;
    this->color = color;
}


GLfloat Light::getInensity() {
    return this->intensity;
}

glm::vec3 Light::getColor() {
    return this->color;
}
