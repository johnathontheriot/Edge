//
//  Spin.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/7/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "Spin.hpp"
#include "GLObject.hpp"
#include "InputManager.hpp"

Spin::Spin(GLObject * target) {
}


void Spin::tick(GLObject * target) {
    InputManager * inputManager = InputManager::getInstance();
    if (inputManager->isKeyPressed("i")) {
        target->translateGlobal(0, 0, -.1);
    }
    if (inputManager->isKeyPressed("j")) {
        target->translateGlobal(-.1, 0, 0);
    }
    if (inputManager->isKeyPressed("k")) {
        target->translateGlobal(0, 0, .1);
    }
    if (inputManager->isKeyPressed("l")) {
        target->translateGlobal(.1, 0, 0);
    }
    if (inputManager->isKeyPressed("[")) {
        ((Light*)target)->changeInensity(1.0);
    }
    if (inputManager->isKeyPressed("]")) {
        ((Light*)target)->changeInensity(-1.0);
    }
    if (inputManager->isKeyPressed("u")) {
        target->translateGlobal(0, .1, 0);
    }
    if (inputManager->isKeyPressed("o")) {
        target->translateGlobal(0, -.1, 0);
    }
}
