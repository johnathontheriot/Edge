//
//  RigidBody.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/7/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef RigidBody_hpp
#define RigidBody_hpp

#include <stdio.h>
#include <glm/vec3.hpp>
#include "../object/GLObject.hpp"

class Rigidbody {
private:
    glm::vec3 centerOfMass;
    glm::vec3 velocity;
    GLfloat mass;
public:
    Rigidbody(GLObject *);
};

#endif /* RigidBody_hpp */
