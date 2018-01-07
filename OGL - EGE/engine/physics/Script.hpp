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

template <class TargetType>
class Script {
private:
protected:
public:
    Script() {
        
    }
    virtual void tick(TargetType * target) {
        
    }
};

#endif /* Script_hpp */
