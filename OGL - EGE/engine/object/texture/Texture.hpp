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
#include "ShaderProgram.hpp"

class Texture: public IShaderVariable {
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
    virtual void bind(std::string name, ShaderProgram * shader) {
        GLuint textureID = glGetUniformLocation(shader->id, name.c_str());
        glActiveTexture(this->texEnum);
        glBindTexture(GL_TEXTURE_2D, this->id);
        glUniform1i(textureID, this->texIndex);
    }
protected:
};

#endif /* Texture_hpp */
