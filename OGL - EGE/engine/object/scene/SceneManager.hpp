//
//  SceneManager.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/6/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef SceneManager_hpp
#define SceneManager_hpp

#include <stdio.h>
#include <unordered_map>
#include "Scene.hpp"

class SceneManager {
private:
    SceneManager();
public:
    std::unordered_map<std::string, Scene *> * scenes;
    static SceneManager * Instance;
    static SceneManager * getInstance();

};

#endif /* SceneManager_hpp */
