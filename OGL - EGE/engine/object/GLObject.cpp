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
#include "Scene.hpp"

class GLObject;

void GLObject::createVAO(GLuint & id) {
    glGenVertexArrays(1, &id);
}


void GLObject::bindVAO(GLuint & id) {
    glBindVertexArray(id);
}


GLObject::GLObject(GLfloat * vertexBuffer, int vertexBufferSize) {
    this->modelMatrix = glm::mat4x4(1.0f);
    this->localScale = glm::mat4x4(1.0f);
    this->localTranslation = glm::mat4x4(1.0f);
    this->localRotation = glm::mat4x4(1.0f);
    this->globalScale = glm::mat4x4(1.0f);
    this->globalTranslation = glm::mat4x4(1.0f);
    this->globalRotation = glm::mat4x4(1.0f);
    this->vertexBuffer = vertexBuffer;
    this->vertexBufferSize = vertexBufferSize;
    this->createVAO(this->VAOid);
    this->bindVAO(this->VAOid);
    this->createBuffer(this->VBOid);
    this->bindVertices(this->VBOid);
    this->scripts = new std::unordered_map<std::string, Script<GLObject>*>();
}

void GLObject::tick() {
    for (std::unordered_map<std::string, Script<GLObject>*>::const_iterator it = this->scripts->begin(); it != this->scripts->end(); ++it) {
        it->second->tick(this);
    }
}

void GLObject::createBuffer(GLuint & id) {
    glGenBuffers(1, &id);
}

void GLObject::bindVertices(GLuint & bufferID) {
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->vertexBufferSize, this->vertexBuffer, GL_STATIC_DRAW);
}

void GLObject::setProgram(ShaderProgram * shader) {
    this->shader = shader;
}


void GLObject::render(Scene * scene, GLenum drawType) {
    glUseProgram(this->shader->id);
    this->shader->bind(this, scene);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBOid);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, this->vertexBufferSize / 3);
    glDisableVertexAttribArray(0);
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
