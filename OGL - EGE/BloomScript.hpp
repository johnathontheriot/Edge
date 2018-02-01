//
//  BloomScript.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 2/1/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef BloomScript_hpp
#define BloomScript_hpp

#include <stdio.h>
#include "Script.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"

class BloomScript : public Script<Scene> {
public:
    bool active = false;
    BloomProcessor * bloom;
    BloomScript(Scene * target): Script(target) {
        this->bloom = new BloomProcessor(new Dimensions(1600, 900));
    }
    virtual void tick() {
        InputManager * inputManager = InputManager::getInstance();
        if (inputManager->keyDown("b")) {
            if (active) {
                this->target->imageEffects->clear();
            } else {
                this->target->imageEffects->insert(this->target->imageEffects->begin(), bloom->processors->begin(), bloom->processors->end());
            }
            active = !active;
        }
        if (inputManager->isKeyPressed("1")) {
            bloom->lowerThreshold += 0.01;
        }
        if (inputManager->isKeyPressed("2")) {
            bloom->lowerThreshold -= 0.01;
        }
        if (inputManager->isKeyPressed("3")) {
            bloom->upperThreshold += 0.01;
        }
        if (inputManager->isKeyPressed("4")) {
            bloom->upperThreshold -= 0.01;
        }
    }
};

#endif /* BloomScript_hpp */
