//
//  SkyBox.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/11/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef SkyBox_hpp
#define SkyBox_hpp

#include <stdio.h>
#include "GLObject.hpp"

class SkyBox: public GLObject {
private:
public:
    template <class ScriptType>
    void attachScript(std::string name) {
        IScriptable::attachScript<ScriptType, SkyBox>(name);
    }
    virtual void render(Scene*);
    SkyBox(std::string texturePath);
    SkyBox(std::string, std::string, std::string, std::string, std::string, std::string);
};
#endif /* SkyBox_hpp */
