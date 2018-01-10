//
//  BasicMovement.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/8/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "BasicMovement.hpp"
#include "System.hpp"
#include "InputManager.hpp"

BasicMovement::BasicMovement(Camera * target) {
    InputManager::getInstance()->addScrollEvent("zoomCamera", [this, target](double xOffset, double yOffset){
        target->zoom(yOffset * .06);
    });
}

void BasicMovement::tick(Camera * target) {
    InputManager * inputManager = InputManager::getInstance();
    if (inputManager->isKeyPressed("w")) {
        target->translateGlobal(0, 0, .001);
    }
    if (inputManager->isKeyPressed("a")) {
        target->translateGlobal(-.001, 0, 0);
    }
    if (inputManager->isKeyPressed("s")) {
        target->translateGlobal(0, 0, -.001);
    }
    if (inputManager->isKeyPressed("d")) {
        target->translateGlobal(.001, 0, 0);
    }
    if (inputManager->isKeyPressed("comma")) {
        target->changeFOV(.4);
    }
    if (inputManager->isKeyPressed("period")) {
        target->changeFOV(-.4);
    }
    if (inputManager->isMouseDown("left")) {
        GLfloat deltaX;
        GLfloat deltaY;
        inputManager->mouseDelta(deltaX, deltaY);
        target->moveCamera(deltaX * (.006f), deltaY * (.006f));

    }
    
}

