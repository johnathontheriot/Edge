//
//  CubeMap.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/12/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef CubeMap_hpp
#define CubeMap_hpp

#include <stdio.h>
#include "Texture.hpp"

class TextureManager;

class CubeMap: public Texture {
private:
    Texture * left;
    Texture * front;
    Texture * right;
    Texture * back;
    Texture * top;
    Texture * bottom;
public:
    GLuint id;
    CubeMap(Texture*, Texture*, Texture*, Texture*, Texture*, Texture*);
    virtual void bind(int txEnum, int txIdx);
protected:
};

#endif /* CubeMap_hpp */
