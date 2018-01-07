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
#include "GLObject.hpp"

ShaderProgram::ShaderProgram(GLSLShader * vertexShader, GLSLShader * fragmentShader) {
    GLint result = GL_FALSE;
    int resLength;
    this -> vertexShader = vertexShader;
    this->fragmentShader = fragmentShader;
    
    this->id = glCreateProgram();
    glAttachShader(this->id, vertexShader->shaderID);
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
    obj->shader->bind4fMatrix("modelTransform", obj->getModelMatrix());
    obj->shader->bind4fMatrix("viewTransform", scene->cameras->at("main")->viewMatrix);

    if (this->bindVars) {
        bindVars(obj, scene);
    }
}

void ShaderProgram::bind4fMatrix(std::string name, glm::mat4x4 mat) {
    GLuint matrixID = glGetUniformLocation(this->id, name.c_str());
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mat[0][0]);
}
