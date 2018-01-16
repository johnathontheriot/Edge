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
#include "../Camera.hpp"
#include <unordered_map>
#include "../GLObject.hpp"
#include "Script.hpp"


class GLObject;

class Scene {
private:
public:
    std::unordered_map<std::string, Camera*> * cameras;
    std::unordered_map<std::string, Script<Scene>*> * scripts;
    template <class ScriptType> void attachScript(std::string name);
    std::unordered_map<std::string, GLObject*> * objects;
    void render();
    void tick();
    Scene(GLFWwindow * window);
    template<class ObjectType, typename std::enable_if<std::is_base_of<GLObject, ObjectType>::value>::type* = nullptr>
    ObjectType * get(std::string key) {
        try {
            return (ObjectType*)(this->objects->at(key));
        }
        catch (std::string & s) {
            return NULL;
        }
    }
};

#endif /* Scene_hpp */
