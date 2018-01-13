//
//  ShaderManager.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/6/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef ShaderManager_hpp
#define ShaderManager_hpp

#include "GLSLShader.hpp"
#include "ShaderProgram.hpp"
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ShaderManager {
public:
    static GLSLShader * loadShader(std::string filePath, GLenum shaderType);
    static ShaderProgram * createShaderProgram(std::string, std::string);
    static ShaderProgram * createShaderProgram(GLSLShader*, GLSLShader*);
    static ShaderProgram * createShaderProgram(std::string, std::string, std::string);
    static ShaderProgram * createShaderProgram(GLSLShader*, GLSLShader*, GLSLShader*);
};

#endif /* ShaderManager_hpp */
