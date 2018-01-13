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
    }
    if (uvBuffer) {
        this->createBuffer(this->UVOid);
    }
    this->bindBuffers();
}

void Geometry::createBuffer(GLuint & id) {
    glGenBuffers(1, &id);
}

void Geometry::bindBuffers() {
    if (this->VBOid) {
        this->bindBuffer<GLfloat>(this->VBOid, this->vertexBuffer, this->vertexBufferSize);
    }
    if (this->UVOid) {
        this->bindBuffer<GLfloat>(this->UVOid, this->uvBuffer, (this->vertexBufferSize / 3) * 2);
    }
    if (this->CBOid) {
        this->bindBuffer<GLfloat>(this->CBOid, this->colorBuffer, this->vertexBufferSize);
    }
}

void Geometry::updateUVs(GLfloat * uvs) {
    if (this->UVOid) {
        this->uvBuffer = uvs;
        this->bindVAO(this->VAOid);
        this->bindBuffer<GLfloat>(this->UVOid, this->uvBuffer, (this->vertexBufferSize / 3) * 2);
    }
}

void Geometry::updateVertices(GLfloat * vertices) {
    if (this->VBOid) {
        this->vertexBuffer = vertices;
        this->bindVAO(this->VAOid);
        this->bindBuffer<GLfloat>(this->VBOid, this->vertexBuffer, this->vertexBufferSize);
    }
}


Geometry::Geometry() {
    
}
