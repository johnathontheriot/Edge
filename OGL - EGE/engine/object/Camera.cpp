//
//  Camera.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/6/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "Camera.hpp"
#include <glm/mat4x4.hpp>

Camera::Camera() {
    this->viewMatrix = glm::mat4x4(1.0f);
}
