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
    
    SkyBox(std::string texturePath);
};
#endif /* SkyBox_hpp */
