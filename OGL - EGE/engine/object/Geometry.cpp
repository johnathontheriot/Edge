//
//  Geometry.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/7/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "Geometry.hpp"

void Geometry::createVAO(GLuint & id) {
    glGenVertexArrays(1, &id);
}


void Geometry::bindVAO(GLuint & id) {
    glBindVertexArray(id);
}

Geometry::Geometry(GLfloat * vertexBuffer, int vertexBufferSize) {
    this->vertexBuffer = vertexBuffer;
    this->vertexBufferSize = vertexBufferSize;
    this->drawType = GL_TRIANGLES;
    this->createVAO(this->VAOid);
    this->bindVAO(this->VAOid);
    this->createBuffer(this->VBOid);
    this->bindVertices(this->VBOid);
}

void Geometry::createBuffer(GLuint & id) {
    glGenBuffers(1, &id);
}

void Geometry::bindVertices(GLuint & bufferID) {
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->vertexBufferSize, this->vertexBuffer, GL_STATIC_DRAW);
}

Geometry::Geometry() {
    
}
