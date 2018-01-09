//
//  InputManager.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/8/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef InputManager_hpp
#define InputManager_hpp

#include <stdio.h>
#include <unordered_map>

class InputManager {
private:
    InputManager();
public:
    static InputManager * Instance;
    static InputManager * getInstance();
};

#endif /* InputManager_hpp */


