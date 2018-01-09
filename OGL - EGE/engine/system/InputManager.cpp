//
//  InputManager.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/8/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "InputManager.hpp"

InputManager * InputManager::Instance;


InputManager * InputManager::getInstance() {
    if (!InputManager::Instance) {
        InputManager::Instance = new InputManager();
    }
    return InputManager::Instance;
}

InputManager::InputManager() {


}
