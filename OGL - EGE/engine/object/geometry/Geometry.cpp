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
    this->buffers = new std::unordered_map<std::string, BufferObject*>();
    this->drawType = GL_TRIANGLES;
    this->createVAO(this->VAOid);
    this->bindVAO(this->VAOid);
    this->buffers->insert({"vertex", new GLBufferObject<GLfloat>(this->bufferListSize++, 3, GL_FLOAT, vertexBufferSize, vertexBuffer)});
    this->buffers->insert({"uvs", new GLBufferObject<GLfloat>(this->bufferListSize++, 2, GL_FLOAT, (vertexBufferSize / 3) * 2, uvBuffer)});
    //this->buffers->insert({"colors", new GLBufferObject<GLfloat>(this->bufferListSize++, 3, GL_FLOAT, vertexBufferSize, vertexBuffer)});

    this->bindBuffers();
}

void Geometry::bindBuffers() {
    for( std::unordered_map<std::string, BufferObject*>::const_iterator it = this->buffers->begin(); it != this->buffers->end(); ++it ) {
        it->second->bind();
    }
}

void Geometry::updateUVs(GLfloat * uvs, int size) {
    if (this->buffers->find("uvs") !=  this->buffers->end()) {
        this->bindVAO(this->VAOid);
        this->buffers->at("uvs")->update(uvs, size);
    }
}

void Geometry::updateVertices(GLfloat * vertices, int size) {
    if (this->buffers->find("vertex") !=  this->buffers->end()) {
        this->bindVAO(this->VAOid);
        this->buffers->at("vertex")->update(vertices, size);
    }
}

int Geometry::getVertexBufferSize(std::string key) {
    if (this->buffers->find(key) !=  this->buffers->end()) {
        return this->buffers->at(key)->size / this->buffers->at(key)->dimension;
    }
    else {
        return 0;
    }
}



Geometry::Geometry() {
    
}
