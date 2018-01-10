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

Geometry::Geometry(GLfloat * vertexBuffer, int vertexBufferSize, GLfloat * uvBuffer) {
    this->vertexBuffer = vertexBuffer;
    this->uvBuffer = uvBuffer;
    this->vertexBufferSize = vertexBufferSize;
    this->drawType = GL_TRIANGLES;
    this->createVAO(this->VAOid);
    this->bindVAO(this->VAOid);
    if (vertexBuffer) {
        this->createBuffer(this->VBOid);
        this->bindBuffer<GLfloat>(this->VBOid, this->vertexBuffer, this->vertexBufferSize);
    }
    if (uvBuffer) {
        this->createBuffer(this->UVOid);
        this->bindBuffer<GLfloat>(this->UVOid, this->uvBuffer, (this->vertexBufferSize / 3) * 2);
    }
}

void Geometry::createBuffer(GLuint & id) {
    glGenBuffers(1, &id);
}


Geometry::Geometry() {
    
}
