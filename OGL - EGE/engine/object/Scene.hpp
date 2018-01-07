//
//  Scene.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/6/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include "Camera.hpp"
#include <unordered_map>
#include "GLObject.hpp"

class GLObject;

class Scene {
private:
public:
    std::unordered_map<std::string, Camera*> * cameras;
    std::unordered_map<std::string, GLObject*> * objects;
    void render();
    Scene();
};

#endif /* Scene_hpp */
