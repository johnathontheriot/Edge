//
//  SceneManager.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/6/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "SceneManager.hpp"

SceneManager * SceneManager::Instance;


SceneManager * SceneManager::getInstance() {
    if (!SceneManager::Instance) {
        SceneManager::Instance = new SceneManager();
    }
    return SceneManager::Instance;
}

SceneManager::SceneManager() {
    this->scenes = new std::unordered_map<std::string, Scene*>();
}
