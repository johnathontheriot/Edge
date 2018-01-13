//
//  Texture.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/7/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Texture {
private:
public:
    int texIndex;
    int texEnum;
    int width;
    int height;
    unsigned char * data;
    GLuint id;
    Texture(int width, int height, unsigned char * data);
    Texture();
    virtual void bind(int txEnum, int txIdx);
protected:
};

#endif /* Texture_hpp */
