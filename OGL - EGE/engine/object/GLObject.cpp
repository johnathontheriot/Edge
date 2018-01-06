//
//  GLObject.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/6/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "GLObject.hpp"
#include <iostream>

void GLObject::createVAO(GLuint & id) {
    glGenVertexArrays(1, &id);
}


void GLObject::bindVAO(GLuint & id) {
    glBindVertexArray(id);
}


GLObject::GLObject(GLfloat * vertexBuffer, int vertexBufferSize) {
    this->vertexBuffer = vertexBuffer;
    this->vertexBufferSize = vertexBufferSize;
    this->createVAO(this->VAOid);
    this->bindVAO(this->VAOid);
    this->createBuffer(this->VBOid);
    this->bindVertices(this->VBOid);
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


void GLObject::render(GLenum drawType) {
    glUseProgram(this->shader->id);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBOid);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, this->vertexBufferSize / 3);
    glDisableVertexAttribArray(0);
}
