//
//  ShaderProgram.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/6/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include "GLSLShader.hpp"
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class ShaderProgram {
private:
    GLSLShader * vertexShader;
    GLSLShader * fragmentShader;
public:
    GLuint id;
    ShaderProgram(GLSLShader *, GLSLShader *);
};

#endif /* ShaderProgram_hpp */
