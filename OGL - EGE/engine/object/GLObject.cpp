//
//  GLObject.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/6/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "GLObject.hpp"
#include <iostream>
#include <cmath>

class GLObject;


GLObject::GLObject(Geometry * mesh) {
    this->geometry = mesh;
    this->modelMatrix = glm::mat4x4(1.0f);
    this->localScale = glm::mat4x4(1.0f);
    this->localTranslation = glm::mat4x4(1.0f);
    this->localRotation = glm::mat4x4(1.0f);
    this->globalScale = glm::mat4x4(1.0f);
    this->globalTranslation = glm::mat4x4(1.0f);
    this->globalRotation = glm::mat4x4(1.0f);
    this->textures = new std::vector<Texture*>();
}

GLObject::GLObject() {
    this->modelMatrix = glm::mat4x4(1.0f);
    this->localScale = glm::mat4x4(1.0f);
    this->localTranslation = glm::mat4x4(1.0f);
    this->localRotation = glm::mat4x4(1.0f);
    this->globalScale = glm::mat4x4(1.0f);
    this->globalTranslation = glm::mat4x4(1.0f);
    this->globalRotation = glm::mat4x4(1.0f);
    this->textures = new std::vector<Texture*>();

}



void GLObject::setProgram(ShaderProgram * shader) {
    this->shader = shader;
}


void GLObject::render(Scene * scene, ShaderProgram* program) {
    ShaderProgram * s = program;
    if (program == NULL) {
        s = this->shader;
    }
    glUseProgram(s->id);
    int shaderCallCount = s->subroutineCalls->size();

    s->bind(this, scene);
    for( std::unordered_map<std::string, BufferObject*>::const_iterator it = this->geometry->buffers->begin(); it != this->geometry->buffers->end(); ++it ) {
        it->second->attach();
    }
    do {
        if (shaderCallCount > 0) {
            ShaderSubRoutineCall call = s->subroutineCalls->at(shaderCallCount - 1);
            GLuint routineID = glGetSubroutineIndex(s->id, call.shaderType, call.routineName.c_str());
            glUniformSubroutinesuiv(call.shaderType, 1, &routineID);
            shaderCallCount--;
        }
        glDrawArrays(this->geometry->drawType, 0, this->geometry->getVertexBufferSize("vertex"));
    } while (shaderCallCount > 0);
    for( std::unordered_map<std::string, BufferObject*>::const_iterator it = this->geometry->buffers->begin(); it != this->geometry->buffers->end(); ++it ) {
        it->second->detach();
    }
    

}

glm::mat4x4 GLObject::getModelMatrix() {
    return this->globalTranslation * this->globalRotation * this->globalScale * this->localTranslation * this->localRotation * this->localScale  * this->modelMatrix;
}

glm::mat4x4 GLObject::getLocalModelMatrix() {
    return this->localTranslation * this->localRotation * this->localScale;
}

glm::mat4x4 GLObject::getGlobalModelMatrix() {
    return this->globalTranslation * this->globalRotation * this->globalScale;
}



void GLObject::translateLocal(GLfloat x, GLfloat y, GLfloat z) {
    this->localTranslation = this->localTranslation * glm::mat4x4(1, 0, 0, 0,
                                                                  0, 1, 0, 0,
                                                                  0, 0, 1, 0,
                                                                  x, y, z, 1);
}

void GLObject::scaleLocal(GLfloat x, GLfloat y, GLfloat z) {
    this->localScale = this->localScale * glm::mat4x4(x, 0, 0, 0,
                                                      0, y, 0, 0,
                                                      0, 0, z, 0,
                                                      0, 0, 0, 1);
}

void GLObject::rotateLocal(GLfloat x, GLfloat y, GLfloat z){
    glm::mat4x4 rotation = glm::mat4x4(1.0f);
    rotation = x == 0 ? rotation : rotation * glm::mat4x4(1,  0, 0, 0,
                                                          0, std::cos(x), std::sin(x), 0,
                                                          0, - std::sin(x), std::cos(x), 0,
                                                          0, 0, 0, 1);
    rotation = y == 0 ? rotation : rotation * glm::mat4x4(std::cos(y), 0, - std::sin(y), 0,
                                                          0, 1, 0, 0,
                                                           std::sin(y), 0, std::cos(y), 0,
                                                          0, 0, 0, 1);
    rotation = z == 0 ? rotation : rotation * glm::mat4x4(std::cos(z), std::sin(z), 0, 0,
                                                          - std::sin(z), std::cos(z), 0, 0,
                                                          0, 0, 1, 0,
                                                          0, 0, 0, 1);
    this->localRotation = this->localRotation * rotation;
}

void GLObject::translateGlobal(GLfloat x, GLfloat y, GLfloat z) {
    this->globalTranslation = this->globalTranslation * glm::mat4x4(1, 0, 0, 0,
                                                                  0, 1, 0, 0,
                                                                  0, 0, 1, 0,
                                                                  x, y, z, 1);
}

void GLObject::scaleGlobal(GLfloat x, GLfloat y, GLfloat z) {
    this->globalScale = this->globalScale * glm::mat4x4(x, 0, 0, 0,
                                                      0, y, 0, 0,
                                                      0, 0, z, 0,
                                                      0, 0, 0, 1);
}

void GLObject::rotateGlobal(GLfloat x, GLfloat y, GLfloat z){
    glm::mat4x4 rotation = glm::mat4x4(1.0f);
    rotation = x == 0 ? rotation : rotation * glm::mat4x4(1,  0, 0, 0,
                                                          0, std::cos(x), std::sin(x), 0,
                                                          0, - std::sin(x), std::cos(x), 0,
                                                          0, 0, 0, 1);
    rotation = y == 0 ? rotation : rotation * glm::mat4x4(std::cos(y), 0, - std::sin(y), 0,
                                                          0, 1, 0, 0,
                                                          std::sin(y), 0, std::cos(y), 0,
                                                          0, 0, 0, 1);
    rotation = z == 0 ? rotation : rotation * glm::mat4x4(std::cos(z), std::sin(z), 0, 0,
                                                          - std::sin(z), std::cos(z), 0, 0,
                                                          0, 0, 1, 0,
                                                          0, 0, 0, 1);
    this->globalRotation = this->globalRotation * rotation;
}
