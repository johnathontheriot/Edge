//
//  Script.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/7/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef Script_hpp
#define Script_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <unordered_map>


class IScript {
public:
    virtual void tick() = 0;
};

template <class TargetType>
class Script: public IScript {
private:
protected:
    TargetType * target;
public:
    Script(TargetType * target) {
        this->target = target;
    }
    virtual void tick() = 0;
};

class IScriptable {
private:
    
public:
    virtual void tick() {
        for (typename std::unordered_map<std::string, IScript*>::const_iterator it = this->scripts->begin(); it != this->scripts->end(); ++it) {
            it->second->tick();
        }
    }
    template <class ScriptType, class ScriptableType>
    void attachScript(std::string name) {
        ScriptType * script = new ScriptType((ScriptableType*)this);
        this->scripts->insert({name, script});
    }
    std::unordered_map<std::string, IScript*> * scripts = new std::unordered_map<std::string, IScript*>();
protected:
};

#endif /* Script_hpp */
