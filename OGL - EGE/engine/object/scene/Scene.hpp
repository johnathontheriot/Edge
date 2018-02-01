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
#include "GLObject.hpp"
#include "Script.hpp"
#include "System.hpp"
#include <list>
#include "Dimensions.hpp"
#include "PostProcessor.hpp"


class IGLObject;
class GLObject;

class Scene: public IScriptable {
private:
public:
    template <class ScriptType>
    void attachScript(std::string name) {
        IScriptable::attachScript<ScriptType, Scene>(name);
    }
    std::list<PostProcessor*> * effectsPipeline;
    std::list<PostProcessor*> * imageEffects;
    Dimensions * viewPort;
    std::unordered_map<std::string, Camera*> * cameras;
    std::unordered_map<std::string, IGLObject*> * objects;
    void render();
    void tick();
    Scene(GLFWwindow * window);
    Scene();
    template<class ObjectType, typename std::enable_if<std::is_base_of<IGLObject, ObjectType>::value>::type* = nullptr>
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
