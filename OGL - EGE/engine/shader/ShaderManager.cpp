//
//  ShaderManager.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/6/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "ShaderManager.hpp"
#include "ShaderProgram.hpp"
#include "GLSLShader.hpp"
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../system/System.hpp"
#include "GLSLShader.hpp"

GLSLShader * ShaderManager::loadShader(std::string filePath, GLenum shaderType) {
    GLint result = GL_FALSE;
    int resLength;
    
    GLuint shaderID = glCreateShader(shaderType);
    std::string fileData = System::getInstance()->readFile(filePath);

    
    char const * fileDataPtr = fileData.c_str();
    glShaderSource(shaderID, 1, &fileDataPtr, NULL);
    glCompileShader(shaderID);
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &resLength);
    if (resLength > 0) {
        std::vector<char> shaderCompileMsg(resLength + 1);
        glGetShaderInfoLog(shaderID, resLength, NULL, &shaderCompileMsg[0]);
        std::cout << filePath << ":: " << &shaderCompileMsg[0];
    }
    
    return new GLSLShader(shaderID);
}



ShaderProgram * ShaderManager::createShaderProgram(std::string vpath, std::string gpath, std::string fpath) {
    return new ShaderProgram(ShaderManager::loadShader(vpath, GL_VERTEX_SHADER), ShaderManager::loadShader(gpath, GL_GEOMETRY_SHADER), ShaderManager::loadShader(fpath, GL_FRAGMENT_SHADER));
}

ShaderProgram * ShaderManager::createShaderProgram(GLSLShader* vShader, GLSLShader* gShader, GLSLShader* fShader) {
    return new ShaderProgram(vShader, gShader, fShader);
}

ShaderProgram * ShaderManager::createShaderProgram(std::string vpath,std::string fpath) {
    return new ShaderProgram(ShaderManager::loadShader(vpath, GL_VERTEX_SHADER), ShaderManager::loadShader(fpath, GL_FRAGMENT_SHADER));
}

ShaderProgram * ShaderManager::createShaderProgram(GLSLShader* vShader, GLSLShader* fShader) {
    return new ShaderProgram(vShader, fShader);
}
