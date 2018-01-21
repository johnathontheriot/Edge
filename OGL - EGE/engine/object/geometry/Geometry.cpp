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
    this->bindVAO(this->VAOid);
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


void Geometry::updateBuffer(std::string key, GLfloat * vertices, int size) {
    if (this->buffers->find(key) !=  this->buffers->end()) {
        this->bindVAO(this->VAOid);
        this->buffers->at(key)->update(vertices, size);
    }
}

void Geometry::generateFaceNormals() {
    GLBufferObject<GLfloat> * vertexBuffer = (GLBufferObject<GLfloat>*)(this->buffers->at("vertex"));
    GLfloat * normalBuffer = new GLfloat[vertexBuffer->size]{ 0.0f };
    for(int i = 0; i < vertexBuffer->size; i += 9) {
        glm::vec3 p1 = glm::vec3(vertexBuffer->data[i], vertexBuffer->data[i + 1], vertexBuffer->data[i + 2]);
        glm::vec3 p2 = glm::vec3(vertexBuffer->data[i + 3], vertexBuffer->data[i + 4], vertexBuffer->data[i + 5]);
        glm::vec3 p3 = glm::vec3(vertexBuffer->data[i + 6], vertexBuffer->data[i + 7], vertexBuffer->data[i + 8]);
        glm::vec3 s1 = p3 - p2;
        glm::vec3 s2 = p1 - p2;
        glm::vec3 normal = glm::cross(s1, s2);
        for (int j = 0; j < 9; j += 3) {
            normalBuffer[i + j] = normal.r;
            normalBuffer[i + j + 1] = normal.g;
            normalBuffer[i + j + 2] = normal.b;
        }
    }
    if (this->buffers->find("normals") ==  this->buffers->end()) {
        this->buffers->insert({"normals", new GLBufferObject<GLfloat>(this->bufferListSize++, 3, GL_FLOAT, vertexBuffer->size, normalBuffer)});
        this->buffers->at("normals")->bind();
    }
    else {
        this->buffers->at("normals")->update(normalBuffer, vertexBuffer->size);
    }
}

std::string vecToString(glm::vec3 vector) {
    return std::to_string(vector.r) + "&" + std::to_string(vector.g) + "&" + std::to_string(vector.b);
}

glm::vec3 keyToVector(char * key) {
    char ** flts = new char*[3];
    for (int i = 0; i < 3; i++) {
        flts[i] = std::strtok(key, "&");
    }
    return glm::vec3(strtof(flts[0], 0), strtof(flts[1], 0), strtof(flts[2], 0));
}

void Geometry::generateVertexNormals() {
    if (this->drawType == GL_TRIANGLES) {
        GLBufferObject<GLfloat> * vertexBuffer = (GLBufferObject<GLfloat>*)(this->buffers->at("vertex"));
        GLfloat * normalBuffer = new GLfloat[vertexBuffer->size]{ 0.0f };
        std::unordered_map<std::string, glm::vec3> * normals = new std::unordered_map<std::string, glm::vec3>();
        for(int i = 0; i < vertexBuffer->size; i += 9) {
            glm::vec3 p1 = glm::vec3(vertexBuffer->data[i], vertexBuffer->data[i + 1], vertexBuffer->data[i + 2]);
            glm::vec3 p2 = glm::vec3(vertexBuffer->data[i + 3], vertexBuffer->data[i + 4], vertexBuffer->data[i + 5]);
            glm::vec3 p3 = glm::vec3(vertexBuffer->data[i + 6], vertexBuffer->data[i + 7], vertexBuffer->data[i + 8]);
            glm::vec3 s1 = p3 - p2;
            glm::vec3 s2 = p1 - p2;
            glm::vec3 normal = glm::cross(s1, s2);
            if (normals->find(vecToString(p1)) == normals->end()) {
                normals->insert({vecToString(p1), normal});
            }
            else {
                normals->at(vecToString(p1)) = normals->at(vecToString(p1)) + normal;
            }
        
            if (normals->find(vecToString(p2)) == normals->end()) {
                normals->insert({vecToString(p2), normal});
            }
            else {
                normals->at(vecToString(p2)) = normals->at(vecToString(p2)) + normal;
            }
        
            if (normals->find(vecToString(p3)) == normals->end()) {
                normals->insert({vecToString(p3), normal});
            }
            else {
                normals->at(vecToString(p3)) = normals->at(vecToString(p3)) + normal;
            }
        }
        for(int i = 0; i < vertexBuffer->size; i += 3) {
            glm::vec3 vertex = glm::vec3(vertexBuffer->data[i], vertexBuffer->data[i + 1], vertexBuffer->data[i + 2]);
            glm::vec3 n = normals->at(vecToString(vertex));
            normalBuffer[i] = n.r;
            normalBuffer[i + 1] = n.g;
            normalBuffer[i + 2] = n.b;
        }
        if (this->buffers->find("normals") ==  this->buffers->end()) {
            this->buffers->insert({"normals", new GLBufferObject<GLfloat>(this->bufferListSize++, 3, GL_FLOAT, vertexBuffer->size, normalBuffer)});
            this->buffers->at("normals")->bind();
        }
        else {
            this->buffers->at("normals")->update(normalBuffer, vertexBuffer->size);
        }
    }
}


Geometry::Geometry() {
    this->buffers = new std::unordered_map<std::string, BufferObject*>();
    this->drawType = GL_POINTS;
    this->createVAO(this->VAOid);
    this->bindVAO(this->VAOid);
}
