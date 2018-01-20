//
//  ShaderProgram.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/6/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "ShaderProgram.hpp"
#include "GLSLShader.hpp"
#include "iostream"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

ShaderProgram::ShaderProgram(GLSLShader * vertexShader, GLSLShader * fragmentShader): ShaderProgram(vertexShader, NULL, fragmentShader) {
    
}

ShaderProgram::ShaderProgram(GLSLShader * vertexShader, GLSLShader * geometryShader, GLSLShader * fragmentShader) {
    GLint result = GL_FALSE;
    int resLength;
    this->vertexShader = vertexShader;
    this->fragmentShader = fragmentShader;
    this->geometryShader = geometryShader;
    this->id = glCreateProgram();
    glAttachShader(this->id, vertexShader->shaderID);
    if (this->geometryShader) {
        glAttachShader(this->id, geometryShader->shaderID);
    }
    glAttachShader(this->id, fragmentShader->shaderID);
    glLinkProgram(this->id);
    glGetProgramiv(this->id, GL_LINK_STATUS, &result);
    glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &resLength);
    if ( resLength > 0 ){
        std::vector<char> programCompileErr(resLength + 1);
        glGetProgramInfoLog(this->id, resLength, NULL, &programCompileErr[0]);
        std::cout << &programCompileErr[0];
    }
}

void ShaderProgram::bind(GLObject* obj, Scene * scene) {    
    if (this->bindVars) {
        bindVars(this, obj, scene);
    }
}

void ShaderProgram::bindVariable(std::string name,  GLfloat flt) {
    GLuint floatID = glGetUniformLocation(this->id, name.c_str());
    glUniform1f(floatID, flt);
}

void ShaderProgram::bindVariable(std::string name, glm::mat4x4 mat) {
    GLuint matrixID = glGetUniformLocation(this->id, name.c_str());
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::bindVariable(std::string name, glm::vec4 vec) {
    GLuint vectorID = glGetUniformLocation(this->id, name.c_str());
    glUniform4f(vectorID, vec.r, vec.g, vec.b, vec.a);
}

void ShaderProgram::bindVariable(std::string name, glm::vec3 vec) {
    GLuint vectorID = glGetUniformLocation(this->id, name.c_str());
    glUniform3f(vectorID, vec.r, vec.g, vec.b);
}
