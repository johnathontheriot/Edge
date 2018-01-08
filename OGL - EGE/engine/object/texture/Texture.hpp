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

struct ImageData {
    int width;
    int height;
    unsigned char * data;
    char * extension;
    ImageData(int width, int height, unsigned char * data, char * extension) {
        this->width = width;
        this->height = height;
        this->data = data;
        this->extension = extension;
    }
};

class Texture {
private:
    ImageData * imageProperties;
public:
    GLuint id;
    Texture(GLuint, ImageData*);
    Texture();
protected:
};

#endif /* Texture_hpp */
